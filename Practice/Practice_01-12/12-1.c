#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <mpi.h>

static double *generate_random_numbers(size_t count)
{
    double *result = (double *) malloc(sizeof(*result) * count);
    for (size_t i = 0; i < count; ++i) {
        result[i] = (double) rand();
    }

    return result;
}

static double calculate_average(double *numbers, size_t count)
{
    if (count == 0) return 0;

    double result = 0.0;
    for (size_t i = 0; i < count; ++i) {
        result += numbers[i];
    }
    result /= count;

    return result;
}

int main(int argc, char **argv) {
    double parallel_average_time = 0.0;
    double serial_average_time = 0.0;

    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        parallel_average_time -= MPI_Wtime();
    }

    static const size_t items_per_process = 10;

    double *numbers = NULL;
    if (rank == 0) {
        numbers =
            generate_random_numbers(world_size * items_per_process);
    }

    double *local_numbers =
        (double *) malloc(sizeof(*local_numbers) * items_per_process);

    MPI_Scatter(
        numbers,
        items_per_process,
        MPI_DOUBLE,
        local_numbers,
        items_per_process,
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    double average =
        calculate_average(local_numbers, items_per_process);

    double *partial_averages = NULL;
    if (rank == 0) {
        partial_averages =
            (double *) malloc(sizeof(*partial_averages) * world_size);
    }

    MPI_Gather(
        &average,
        1,
        MPI_DOUBLE,
        partial_averages,
        1,
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {
        average = calculate_average(partial_averages, world_size);
        parallel_average_time += MPI_Wtime();

        printf("Parallel average: %.2f, time: %.2f\n", average, parallel_average_time);

        serial_average_time -= MPI_Wtime();
        average = calculate_average(numbers, world_size * items_per_process);
        serial_average_time += MPI_Wtime();

        printf("Serial average: %.2f, time: %.2f\n", average, serial_average_time);
    }

    if (numbers != NULL) {
        free(numbers);
    }
    free(local_numbers);
    if (partial_averages != NULL) {
        free(partial_averages);
    }

    MPI_Finalize();

    return 0;
}

