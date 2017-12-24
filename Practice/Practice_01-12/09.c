#include <stdio.h>

#include <mpi.h>

static const int Pings = 10;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (world_size != 2) {
        fprintf(stderr, "Only two processes are allowed here.\n");
        return -1;
    }

    int counter = 0;
    int data = 0;
    while (counter < Pings) {
        if (rank == counter % 2) {
            ++data;
            int next_neighbor_rank = (rank + 1) % world_size;
            printf(
                "Process %d out of %d is sending %d to process %d\n",
                rank,
                world_size,
                data,
                next_neighbor_rank
            );
            MPI_Send(
                &data, 1,
                MPI_INT,
                next_neighbor_rank,
                0,
                MPI_COMM_WORLD
            );
        } else {
            int previous_neighbor_rank = (rank + 1) % world_size;
            MPI_Recv(
                &data, 1,
                MPI_INT,
                previous_neighbor_rank,
                0,
                MPI_COMM_WORLD,
                MPI_STATUS_IGNORE
            );
            printf(
                "Process %d out of %d got %d from process %d\n",
                rank,
                world_size,
                data,
                previous_neighbor_rank
            );
        }
        ++counter;
    }

    MPI_Finalize();

    return 0;
}

