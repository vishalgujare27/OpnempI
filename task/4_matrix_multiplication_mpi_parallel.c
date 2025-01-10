#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int i, j, k, rank, size, n = 1000;
    int *A, *B, *C, *sub_A, *sub_C;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int chunksize = n * n / size;


    if (rank == 0) {
        A = (int*)malloc(n * n * sizeof(int));
        B = (int*)malloc(n * n * sizeof(int));
        C = (int*)malloc(n * n * sizeof(int));
        for (i = 0; i < n * n; i++) {
            A[i] = 1;
            B[i] = 1;
            C[i] = 0;
        }
    } else {
        B = (int*)malloc(n * n * sizeof(int));
    }

   
    sub_A = (int*)malloc(chunksize * sizeof(int));
    sub_C = (int*)malloc(chunksize * sizeof(int));
    for (i = 0; i < chunksize; i++) {
        sub_C[i] = 0;
    }

    MPI_Bcast(B, n * n, MPI_INT, 0, MPI_COMM_WORLD);

  
    MPI_Scatter(A, chunksize, MPI_INT, sub_A, chunksize, MPI_INT, 0, MPI_COMM_WORLD);


    for (i = 0; i < chunksize / n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                sub_C[i * n + j] += sub_A[i * n + k] * B[k * n + j];
            }
        }
    }

 
    MPI_Gather(sub_C, chunksize, MPI_INT, C, chunksize, MPI_INT, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        int flag = 1;
        for (i = 0; i < n * n; i++) {
            if (C[i] != n) {
                flag = 0;
                break;
            }
        }
        if (flag) printf("_____PASS_____\n");
        else printf("_____FAIL_____\n");


        free(A);
        free(B);
        free(C);
    } else {
        free(B);
    }

    free(sub_A);
    free(sub_C);

    MPI_Finalize();
    return 0;
}
