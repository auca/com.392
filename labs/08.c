#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int num_of_processes;
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_processes);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf(
            "Hello, from a master process %d.\n" \
            "Waiting for messages.\n",
            rank
        );

        #define MAX_MESSAGE_LENGTH 1024
        static char message[MAX_MESSAGE_LENGTH];
        for (int i = 1; i < num_of_processes; ++i) {
            MPI_Recv(
                message,
                MAX_MESSAGE_LENGTH,
                MPI_CHAR,
                i, 0,
                MPI_COMM_WORLD,
                MPI_STATUS_IGNORE
            );
            message[MAX_MESSAGE_LENGTH - 1] = '\0';

            printf(
                "Got a message '%s'.\n",
                message
            );
        }
    } else {
        printf(
            "Hello, from a generic process %d out of %d.\n",
            rank,
            num_of_processes
        );

        static const char message[] = "hello";
        MPI_Send(
            message,
            sizeof(message),
            MPI_CHAR,
            0, 0,
            MPI_COMM_WORLD
        );
    }

    MPI_Finalize();

    return 0;
}
