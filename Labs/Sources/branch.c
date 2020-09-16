#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define num_t int // must always be int for this test
#define NUM_COUNT 10 * 1024 * 1024

static const int Max_Rand = 10;
static const size_t Benchmark_Reps = 20;
static const num_t Sum_Cut_Off = 6;
static num_t Numbers[NUM_COUNT];

static int _compare_numbers(const void *a, const void *b)
{
    return *((num_t *) a) - *((num_t *) b);
}

static void fill_array_with_random_numbers(num_t *numbers, size_t count, int max_rand)
{
    srand(1); // keep the values the same between runs
    for (size_t i = 0; i < count; ++i) {
        numbers[i] = (num_t) ((double) rand() / ((double) RAND_MAX + 1) * max_rand);
    }
}

static void load_array_with_random_numbers(num_t *numbers, size_t count)
{
    FILE *fd = fopen("branch.data", "r");
    fread(numbers, sizeof(num_t), count, fd);
    fclose(fd);
}

static void write_array_with_random_numbers(num_t *numbers, size_t count)
{
    FILE *fd = fopen("branch.data", "w+");
    fwrite(numbers, sizeof(num_t), count, fd);
    fclose(fd);
}

static num_t sum_numbers_less_than_value(num_t *numbers, size_t count, num_t value)
{
    num_t result = 0;

    for (size_t i = 0; i < Benchmark_Reps; ++i) {
        for (size_t j = 0, limit = count - 1; j < limit; ++j) {
            if (numbers[j] < value) {
                result += numbers[j];
            }
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    if (argc > 1 && argv[1][1] == 'g') {
        fill_array_with_random_numbers(Numbers, NUM_COUNT, Max_Rand);
        if (argc > 2 && argv[2][1] == 's') {
            qsort(Numbers, NUM_COUNT, sizeof(num_t), _compare_numbers);
        }
        write_array_with_random_numbers(Numbers, NUM_COUNT);

        return 0;
    }

    load_array_with_random_numbers(Numbers, NUM_COUNT);

    num_t sum = sum_numbers_less_than_value(Numbers, NUM_COUNT, Sum_Cut_Off);
    printf(
        "The sum of numbers less than %lld in an array of random numbers is %lld\n",
        (long long) Sum_Cut_Off,
        (long long) sum
    );

    return 0;
}

