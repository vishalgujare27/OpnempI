#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void perform_computation(int rank) {
    printf("Process %d performing computation\n", rank);

    sleep(2);
}

void perform_io_operations(int rank) {
    printf("Process %d performing I/O operations\n", rank);

    sleep(3);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int half_size = size / 2;
    int *even_ranks = malloc(half_size * sizeof(int));
    int *odd_ranks = malloc((size - half_size) * sizeof(int));

    int even_count = 0, odd_count = 0;
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            even_ranks[even_count] = i;
            even_count++;
        } else {
            odd_ranks[odd_count++] = i;
        }
    }

    MPI_Group world_group, even_group, odd_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
    MPI_Group_incl(world_group, even_count, even_ranks, &even_group);
    MPI_Group_incl(world_group, odd_count, odd_ranks, &odd_group);


    MPI_Comm even_comm, odd_comm;
    MPI_Comm_create_group(MPI_COMM_WORLD, even_group, 0, &even_comm);
    MPI_Comm_create_group(MPI_COMM_WORLD, odd_group, 1, &odd_comm);

    if (rank % 2 == 0 && even_comm != MPI_COMM_NULL) {
        perform_computation(rank);
    } else if (rank % 2 != 0 && odd_comm != MPI_COMM_NULL) {
        perform_io_operations(rank);
    }


    MPI_Group_free(&even_group);
    MPI_Group_free(&odd_group);
    if (even_comm != MPI_COMM_NULL) MPI_Comm_free(&even_comm);
    if (odd_comm != MPI_COMM_NULL) MPI_Comm_free(&odd_comm);
    MPI_Group_free(&world_group);

    free(even_ranks);
    free(odd_ranks);

    MPI_Finalize();
    return 0;
}
