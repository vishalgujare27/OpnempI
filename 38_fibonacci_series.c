
#include<stdio.h>
#include <stdlib.h>
#include <mpi.h>

int
main ()
{
  int rank, size;
  MPI_Init (NULL, NULL);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  int local_digit = 0;
  int first = 0;
  int second = 0;

  if (rank == 0)
    {
      local_digit = 0;
      if (rank + 2 < size)
	{
	  MPI_Send (&local_digit, 1, MPI_INT, rank + 2, 1, MPI_COMM_WORLD);
	}
    }

  if (rank == 1)
    {
      local_digit = 1;
      if (rank + 1 < size)
	{
	  MPI_Send (&local_digit, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
	}
      if (rank + 2 < size)
	{
	  MPI_Send (&local_digit, 1, MPI_INT, rank + 2, 1, MPI_COMM_WORLD);
	}
    }

  if (rank != 0 && rank != 1)
    {
      MPI_Recv (&first, 1, MPI_INT, rank - 2, 1, MPI_COMM_WORLD,
		MPI_STATUS_IGNORE);
      MPI_Recv (&second, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,
		MPI_STATUS_IGNORE);

      local_digit = first + second;

      if (rank + 1 < size)
	{
	  MPI_Send (&local_digit, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
	}
      if (rank + 2 < size)
	{
	  MPI_Send (&local_digit, 1, MPI_INT, rank + 2, 1, MPI_COMM_WORLD);
	}

      printf ("rank %d first digit %d second %d local %d\n", rank, first,
	      second, local_digit);
    }

  MPI_Finalize ();
  return 0;
}
