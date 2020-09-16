#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define num_t int
#define NUM_COUNT 4 * 1024 * 1024

static const int Max_Rand = 5;
static const size_t Benchmark_Reps = 50;
static num_t Numbers[NUM_COUNT];

static void fill_array_with_random_numbers(num_t *numbers, size_t count, int max_rand)
{
    srand(1); // keep the values the same between runs
    for (size_t i = 0; i < count; ++i) {
        numbers[i] = (num_t) ((double) rand() / ((double) RAND_MAX + 1) * max_rand);
    }
}

static num_t sum_numbers_with_approach_1(num_t *numbers, size_t count)
{
    num_t result = 0;

    for (size_t i = 0; i < Benchmark_Reps; ++i) {
        for (size_t j = 0, limit = count - 1; j < limit; ++j) {
            result += numbers[j];
            result += numbers[j];
            result += numbers[j + 1];
            result += numbers[j + 1];
        }
    }

    return result;
}

static num_t sum_numbers_with_approach_2(num_t *numbers, size_t count)
{
    num_t a = 0, b = 0, c = 0, d = 0;

    for (size_t i = 0; i < Benchmark_Reps; ++i) {
        for (size_t j = 0, limit = count - 1; j < limit; ++j) {
            a += numbers[j];
            b += numbers[j];
            c += numbers[j + 1];
            d += numbers[j + 1];
        }
    }

    return a + b + c + d;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <type of the approach to sum random numbers (1 or 2)>\n", argv[0]);
        return 1;
    }

    fill_array_with_random_numbers(Numbers, NUM_COUNT, Max_Rand);

    num_t sum;
    int approach = (int) strtol(argv[1], NULL, 10);
    if (approach == 1) {
        sum = sum_numbers_with_approach_1(Numbers, NUM_COUNT);
    } else if (approach == 2) {
        sum = sum_numbers_with_approach_2(Numbers, NUM_COUNT);
    } else {
        fputs("Invalid approach selector. It should be a number 1 or 2.\n", stderr);
        return 1;
    }
    printf("The sum of an array of random numbers is %lld\n", (long long) sum);

    return 0;
}

