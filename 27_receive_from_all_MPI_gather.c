#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    MPI_Init(NULL,NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 10;
    int *array = (int*)malloc(N * sizeof(int));
    int *totarr = NULL;
    for (int i = 0; i < N; i++) {
        array[i] = i + 1;
    }
    if (rank == 0) {

        totarr = (int*)malloc(N * size * sizeof(int));
    }
MPI_Gather(array,N,MPI_INT,totarr,N,MPI_INT,0,MPI_COMM_WORLD);

if(rank == 0){
   printf("Gathered data at root process: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", totarr[i]);
        }
        printf("\n");

        free(totarr);
    }
    free(array);
    MPI_Finalize();
    return 0;
}
