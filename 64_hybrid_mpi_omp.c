#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int provided;

 
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

    
    if (provided !=  MPI_THREAD_MULTIPLE) {
        printf("MPI does not provide required thread support\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }


    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);


    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    #pragma omp parallel num_threads(5)
    {
        printf("thread %d inside rank %d\n", omp_get_thread_num(), rank);
    }

    
         MPI_Finalize();
             return 0;
         }
