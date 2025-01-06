#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 100000000

int main() {
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

long long    int chunksize = N / size;
   long long  int* global_arr = NULL;
long long  int* local_arr = (long long int*)malloc(chunksize * sizeof(long long int));

    if (rank == 0) {
        global_arr = (long long int*)malloc(N * sizeof(long long int));
        for (long int i = 0; i < N; i++) {
            global_arr[i] = i + 1;
        }
    }
double start_time = MPI_Wtime();

    MPI_Scatter(global_arr, chunksize, MPI_LONG_LONG_INT, local_arr, chunksize, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);

  long long  int local_sum = 0;
    for (long int i = 0; i < chunksize; i++) {
        local_sum += local_arr[i];
    }

    long long int* global_sums = NULL;
    if (rank == 0) {
        global_sums = (long long int*)malloc(size * sizeof(long long int));
    }

    MPI_Gather(&local_sum, 1, MPI_LONG_LONG_INT, global_sums, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
       long long int total_sum = 0;
        for (long int i = 0; i < size; i++) {
            total_sum += global_sums[i];
        }

        printf("\nTotal sum = %lld\n", total_sum);
double end_time = MPI_Wtime();
if(rank == 0 ){
printf("Total time taken : %lf ",(end_time - start_time) );

}
        free(global_arr);
        free(global_sums);
    }

    free(local_arr);
    MPI_Finalize();
    return 0;
}
