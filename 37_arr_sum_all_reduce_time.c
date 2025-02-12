#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 100000000

int main() {
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
double start_time , end_time ;    
long long int chunksize = N / size;
   long long int* global_arr = NULL;
   long long int* local_arr = (long long int*)malloc(chunksize * sizeof(long long int));
    if (rank == 0) {
        global_arr = (long long int*)malloc(N * sizeof(long long int));
        for (long int i = 0; i < N; i++) {
            global_arr[i] = i + 1;
        }
    }

if (rank == 0 )start_time = MPI_Wtime();



    MPI_Scatter(global_arr, chunksize, MPI_LONG_LONG_INT, local_arr, chunksize, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);
   long long int local_sum = 0;
    for (long int i = 0; i < chunksize; i++) {
        local_sum += local_arr[i];
    }
   long long  int final_sum;
    MPI_Allreduce(&local_sum, &final_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

if (rank == 0)  end_time = MPI_Wtime();


    printf("rank = %d\ttotal sum = %ld\n", rank, final_sum);
    if(rank == 0){
printf("Total time taken : %lf ",(end_time - start_time) );

        free(global_arr);
    }
    free(local_arr);
    MPI_Finalize();
    return 0;
}
