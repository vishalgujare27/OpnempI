#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>

#define N 999999999

int main(int argc, char* argv[]) {
    int rank, size, i;
    
    double dx, local_area, total_area, x, y;
    double start_time, end_time;
    int start, end, chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    dx = 1.0 / N;
    chunk_size = N / size;

    start = rank * chunk_size;
    end = (rank +1) * chunk_size;
    if (rank == size - 1) {
        end = N;
    }

    local_area = 0.0;

    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    for (i = start; i < end; i++) {
        x = i * dx;
        y = sqrt(1 - x * x);
        local_area += y * dx;
    }

    MPI_Reduce(&local_area, &total_area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        end_time = MPI_Wtime();
        double pi = 4.0 * total_area;
        printf("\nValue of pi is = %.16lf\n", pi);
        printf("Execution time is = %lf seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}

