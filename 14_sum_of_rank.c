#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int
main ()
{
  int size, rank;
  MPI_Init (NULL, NULL);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  if (rank == 0)
    {
      int totalsum = 0;
      int localsum = 0;
      for (int i = 1; i < size; i++)
	{

	  MPI_Recv (&localsum, 1, MPI_INT, i, 0, MPI_COMM_WORLD,
		    MPI_STATUS_IGNORE);
	  totalsum += localsum;
	}
      printf ("totalsum = %d\n", totalsum);

    }
  else
    {
      MPI_Send (&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

  MPI_Finalize ();
  return 0;
}