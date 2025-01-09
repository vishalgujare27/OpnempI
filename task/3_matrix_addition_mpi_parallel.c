#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
    int i, j, rank, size, n = 10000;
    int *m1, *m2, *sumMat, *sub_m1, *sub_m2, *sub_sumMat;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int chunksize = (n * n) / size;

  
    if (rank == 0) {
        m1 = (int*)malloc(n * n * sizeof(int));
        m2 = (int*)malloc(n * n * sizeof(int));
        sumMat = (int*)malloc(n * n * sizeof(int));
        for (i = 0; i < n * n; i++) {
            m1[i] = 1;
            m2[i] = 1;
        }
    }

  
    sub_m1 = (int*)malloc(chunksize * sizeof(int));
    sub_m2 = (int*)malloc(chunksize * sizeof(int));
    sub_sumMat = (int*)malloc(chunksize * sizeof(int));

    double startTime = MPI_Wtime();
    
    MPI_Scatter(m1, chunksize, MPI_INT, sub_m1, chunksize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(m2, chunksize, MPI_INT, sub_m2, chunksize, MPI_INT, 0, MPI_COMM_WORLD);

    
    for (i = 0; i < chunksize; i++) {
        sub_sumMat[i] = sub_m1[i] + sub_m2[i];
    }

    
    MPI_Gather(sub_sumMat, chunksize, MPI_INT, sumMat, chunksize, MPI_INT, 0, MPI_COMM_WORLD);

    double endTime = MPI_Wtime();
    
    if (rank == 0) {
        int flag = 1;
        for (i = 0; i < n * n; i++) {
            if (sumMat[i] != 2) {
                flag = 0;
                break;
            }
        }
        if (flag){
          printf("_____PASS_____\n");
          printf("Execution time: %lf\n", endTime - startTime);
        }
        else printf("_____FAIL_____\n");
      
        free(m1);
        free(m2);
        free(sumMat);
    }
    free(sub_m1);
    free(sub_m2);
    free(sub_sumMat);
    MPI_Finalize();
    return 0;
}
