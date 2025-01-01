#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#define N 1000
int
main (int argc, char **argv)
{
  int myid, size;
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &size);


  MPI_Comm_rank (MPI_COMM_WORLD, &myid);


  if (myid == 0)
    {

      int number = 0;
      int total_sum = 0;
      int chunk = N / size;
      int start = myid * chunk;
      int end = start + chunk;

      for (int i = start; i < end; i++)
	{
	  total_sum += i + 1;
	}
      for (int i = 1; i < size; i++)
	{
	  MPI_Recv (&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD,
		    MPI_STATUS_IGNORE);
	  total_sum += number;

	}
      printf ("Total Sum : %d \n", total_sum);

    }
  else
    {
      int local_sum = 0;

      int chunk = N / size;
      int start = myid * chunk;
      int end = start + chunk;

      if (myid == size - 1)
       end = N ;

	for (int i = start; i < end; i++)
	  {
	    local_sum += i + 1;
	  }
      printf ("local Sum : %d rank : %d \n", local_sum, myid);

      MPI_Send (&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }


  MPI_Finalize ();

  return 0;
}
