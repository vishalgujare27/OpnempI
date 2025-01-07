#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

  int data[N][N];
int count  = 10 ;
MPI_Datatype contiguous_type ;

MPI_Type_contiguous(count,MPI_INT,&contiguous_type);
MPI_Type_commit (&contiguous_type) ;

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
int tmp =1 ;
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            data[i][j] = tmp;
            tmp++ ;
        }
        }

        MPI_Send(data, 10, contiguous_type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data:\n ");
        for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
        }
        printf("\n");
    } else if (rank == 1) {
        MPI_Recv(data, 10, contiguous_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data:\n ");
 for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
        }    

    printf("\n");
    }
MPI_Type_free(&contiguous_type);
    MPI_Finalize();
    return 0;
}
