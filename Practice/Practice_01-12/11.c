#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <mpi.h>

static void my_bcast(void *data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator) {
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 0) {
        MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
    } else {
        for (int i = 0; i < world_size; ++i) {
            if (i != rank) {
                MPI_Send(data, count, datatype, i, 0, MPI_COMM_WORLD);
            }
        }
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 1000;
    int *numbers = malloc(sizeof(*numbers) * n);
    int trials = 10;

    double my_bcast_time = 0.0;
    double mpi_bcast_time = 0.0;
    for (int i = 0; i < trials; ++i) {
        MPI_Barrier(MPI_COMM_WORLD);
        my_bcast_time -= MPI_Wtime();
        my_bcast(numbers, n, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        my_bcast_time += MPI_Wtime();

        MPI_Barrier(MPI_COMM_WORLD);
        mpi_bcast_time -= MPI_Wtime();
        MPI_Bcast(numbers, n, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        mpi_bcast_time += MPI_Wtime();
    }

    if (rank == 0) {
        printf("my_bcast time %lf\n", my_bcast_time / n);
        printf("mpi_bcast time %lf\n", mpi_bcast_time / n);
    }

    MPI_Finalize();

    return 0;
}
