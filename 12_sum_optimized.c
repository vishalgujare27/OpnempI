#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int
main ()
{
  int size, rank;
  MPI_Init (NULL, NULL);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  const int n = 1000;
  int *arr = NULL;
  int chunksize = n / size;

  if (rank == 0)
    {
      arr = (int *) malloc (n * sizeof (int));
      for (int i = 0; i < n; i++)
	{
	  arr[i] = i + 1;
	}
    }

  int *local_arr = (int *) malloc (chunksize * sizeof (int));

  if (rank == 0)
    {
      for (int i = 1; i < size; i++)
	{
	  int start = i * chunksize;
	  int end = (i + 1) * chunksize;
	  if (i == size - 1)
	    {
	      end = n;

	    }
	  MPI_Send (arr, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
	}

      for (int i = 0; i < chunksize; i++)
	{
	  local_arr[i] = arr[i];
	}
    }
  else
    {
      int start = rank * chunksize;

      int end = start + chunksize;
      if (rank == size - 1)
	{
	  end = n;

	}



      MPI_Recv (local_arr, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD,
		MPI_STATUS_IGNORE);
    }

  int localsum = 0;
  for (int i = 0; i < chunksize; i++)
    {
      localsum += local_arr[i];
    }

  int totalsum = 0;

  if (rank == 0)
    {
      totalsum = localsum;
      for (int i = 1; i < size; i++)
	{
	  int received_sum;
	  MPI_Recv (&received_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD,
		    MPI_STATUS_IGNORE);
	  totalsum += received_sum;
	}
      printf ("Total sum = %d\n", totalsum);
    }
  else
    {
      MPI_Send (&localsum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

  if (rank == 0)
    {
      free (arr);
    }
  free (local_arr);

  MPI_Finalize ();
  return 0;
}
