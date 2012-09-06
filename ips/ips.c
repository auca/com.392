/*
    ips.c

    Created by Dmitrii Toksaitov on Sat Aug 29 10:12:03 KGT 2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <png.h>

#define IPS_CLAMP(X, MIN, MAX) (((X) > (MAX)) ? (MAX) : (((X) < (MIN)) ? (MIN) : (X)))

#define IPS_ERROR(MESSAGE)                             \
        do {                                           \
            fprintf(stderr, "Error: %s\n", (MESSAGE)); \
            program_status = EXIT_FAILURE;             \
            goto cleanup;                              \
        } while (0)

int main(int argc, char *argv[])
{
    int program_status = EXIT_SUCCESS;

    FILE *input_image_file  = NULL,
         *output_image_file = NULL;

    png_byte input_image_header[1];

    png_structp png_input_image_struct  = NULL,
                png_output_image_struct = NULL;

    png_infop png_input_image_info  = NULL,
              png_output_image_info = NULL;

    png_uint_32 input_image_width,
                input_image_height;

    int input_image_bit_depth,
        input_image_color_type,
        input_image_interlace_type,
        input_image_compression_type,
        input_image_filter_type;

    png_bytep image_row;

    png_uint_32 y;

    int channel;

    if (argc < 3 && argc > 1) {
        IPS_ERROR("output file was not specified");
    } else if (argc < 2) {
        IPS_ERROR("input and output files were not specified");
    }

    input_image_file = fopen(argv[1], "rb");
    if (!input_image_file) {
        IPS_ERROR("failed to open the input image");
    }

    output_image_file = fopen(argv[2], "wb");
    if (!output_image_file) {
        IPS_ERROR("failed to open the output image");
    }

    fread(input_image_header, 1, sizeof(input_image_header), input_image_file);

    if (png_sig_cmp(input_image_header, 0, sizeof(input_image_header))) {
        IPS_ERROR("input file is not a valid PNG file");
    }

    png_input_image_struct = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                                    NULL, NULL, NULL);
    if (!png_input_image_struct) {
        IPS_ERROR("internal error: libpng: read structure was not created");
    }

    png_output_image_struct = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                                        NULL, NULL, NULL);

    if (!png_output_image_struct) {
        IPS_ERROR("internal error: libpng: write structure was not created");
    }

    png_input_image_info = png_create_info_struct(png_input_image_struct);
    if (!png_input_image_info) {
        IPS_ERROR("internal error: libpng: info structure for the input file was not created");
    }

    png_output_image_info = png_create_info_struct(png_output_image_struct);
    if (!png_output_image_info) {
        IPS_ERROR("internal error: libpng: info structure for the output file was not created");
    }

    if (setjmp(png_jmpbuf(png_input_image_struct))) {
        IPS_ERROR("failed to read the image");
    }

    if (setjmp(png_jmpbuf(png_output_image_struct))) {
        IPS_ERROR("failed to create the image");
    }

    png_init_io(png_input_image_struct,  input_image_file);
    png_init_io(png_output_image_struct, output_image_file);

    png_set_sig_bytes(png_input_image_struct, sizeof(input_image_header));

    png_read_info(png_input_image_struct, png_input_image_info);
    png_get_IHDR(png_input_image_struct,
                 png_input_image_info,
                 &input_image_width,
                 &input_image_height,
                 &input_image_bit_depth,
                 &input_image_color_type,
                 &input_image_interlace_type,
                 &input_image_compression_type,
                 &input_image_filter_type);

    if (input_image_interlace_type != PNG_INTERLACE_NONE) {
        IPS_ERROR("interlaced images are not supported");
    }

    if (input_image_color_type != PNG_COLOR_TYPE_RGB ||
        input_image_bit_depth  != 8) {
        IPS_ERROR("only RGB 8-bit images can be processed");
    }

    png_set_IHDR(png_output_image_struct,
                 png_output_image_info,
                 input_image_width,
                 input_image_height,
                 input_image_bit_depth,
                 input_image_color_type,
                 input_image_interlace_type,
                 input_image_compression_type,
                 input_image_filter_type);
    png_write_info(png_output_image_struct, png_output_image_info);

    image_row = (png_bytep) png_malloc(png_input_image_struct, png_get_rowbytes(png_input_image_struct,
                                                                                png_input_image_info));

    for (y = 0; y < input_image_height; ++y) {
        png_read_rows(png_input_image_struct, &image_row, NULL, 1);

        // ToDo: processing

        png_write_rows(png_output_image_struct, &image_row, 1);
    }

    png_free(png_input_image_struct, image_row);
    image_row = NULL;

    png_read_end(png_input_image_struct,   png_input_image_info);
    png_write_end(png_output_image_struct, png_input_image_info);

    fclose(input_image_file);
    input_image_file = NULL;

    fclose(output_image_file);
    output_image_file = NULL;

cleanup:
    if (input_image_file) {
        fclose(input_image_file);
        input_image_file = NULL;
    }

    if (output_image_file) {
        fclose(output_image_file);
        output_image_file = NULL;
    }

    if (png_input_image_info) {
        png_free_data(png_input_image_struct, png_input_image_info, PNG_FREE_ALL, -1);
    }

    if (png_output_image_info) {
        png_free_data(png_output_image_struct, png_output_image_info, PNG_FREE_ALL, -1);
    }

    if (png_input_image_struct) {
        png_destroy_read_struct(&png_input_image_struct, NULL, NULL);
    }

    if (png_output_image_struct) {
        png_destroy_write_struct(&png_output_image_struct, NULL);
    }

    if (program_status != EXIT_SUCCESS) {
        if (remove(argv[2])) {
            perror(NULL);
        }
    }

    return program_status;
}

