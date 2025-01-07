#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 15

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

  
int data[N];
const int count = 3 ;
const int blocklength = 3 ;
const int stride = 6 ;

MPI_Datatype vector_type ;

MPI_Type_vector(count,blocklength,stride,MPI_INT,&vector_type);
MPI_Type_commit (&vector_type) ;

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            data[i] = i + 1  ;
        }

        MPI_Send(data, 1, vector_type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data:\n ");
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    } else if (rank == 1) {
        
 for (int i = 0; i < N; i++) {
            data[i] = 0   ;
}

       MPI_Recv(data, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data:\n ");
 for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }    

    printf("\n");
    }
MPI_Type_free(&vector_type);
    MPI_Finalize();
    return 0;
}
