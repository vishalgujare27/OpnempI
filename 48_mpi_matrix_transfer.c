#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 5

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

  int data[N][N];

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            data[i][j] = i*j + 1;
        }
        }

        MPI_Send(data,N*N,MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data:\n ");
        
for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", data[i][j]);
        }
printf("\n");
}
printf("\n");
    } else if (rank == 1) {
        MPI_Recv(data, N*N,MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data:\n ");
        for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", data[i][j]);
        }
 printf("\n");
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
