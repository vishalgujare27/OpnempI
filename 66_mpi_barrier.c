#include<stdio.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int
main (int argc, char **argv)
{
  MPI_Init (&argc, &argv);

  int rank, size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  if (rank == 0)
    {
      printf ("process %d : processing data : \n", rank);
      sleep(2);
    }

  printf ("Process %d : waiting at the barrier.\n", rank);
  MPI_Barrier (MPI_COMM_WORLD);

  printf ("Process %d : Processing to next phase.\n", rank);

  MPI_Finalize ();

  return 0;
}

