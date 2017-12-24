#include <stdio.h>
#include <stdbool.h>

#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int token = rank != 0 ? 0 : 42;
    printf("Process %d out of %d has a token %d\n", rank, world_size, token);

    while (true) {
        if (rank != 0) {
            int previous_neighbour = rank - 1;
            MPI_Recv(
                &token, 1,
                MPI_INT,
                previous_neighbour,
                0,
                MPI_COMM_WORLD,
                MPI_STATUS_IGNORE
            );

            printf(
                "Process %d out of %d got the token %d from process %d\n",
                rank,
                world_size,
                token,
                previous_neighbour
            );
        }

        int next_neighbour = (rank + 1) % world_size;
        printf(
            "Process %d out of %d is sending the token %d to process %d\n",
            rank,
            world_size,
            token,
            next_neighbour
        );

        MPI_Send(&token, 1, MPI_INT, next_neighbour, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            int last_process = world_size - 1;
            MPI_Recv(
                &token, 1,
                MPI_INT,
                last_process,
                0,
                MPI_COMM_WORLD,
                MPI_STATUS_IGNORE
            );

            printf(
                "Process %d out of %d got the token %d from process %d\n",
                rank,
                world_size,
                token,
                last_process
            );
        }
    }

    MPI_Finalize();

    return 0;
}

