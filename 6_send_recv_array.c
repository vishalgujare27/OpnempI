#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#define N 10000
int
main (int argc, char **argv)
{
  int myid, size;
  int a[N];
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &size);


  MPI_Comm_rank (MPI_COMM_WORLD, &myid);


  if (myid == 0)
    {
      for (int i = 0; i < N; i++)
	{
	  a[i] = i + 1;

	}
      for (int i = 1; i < size; i++)
	{
	  MPI_Send (a, N, MPI_INT, i, 0, MPI_COMM_WORLD);

	  printf ("\nmyid: %d \t DATA sent\t\n", myid);
	}
    }
  else
    {

      MPI_Recv (a, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf ("\nmyid: %d \t DATA received . ", myid);
      for (int i = N - 10; i < N; i++)
	{
	  printf ("%d ", a[i]);

	}

    }







  MPI_Finalize ();

  return 0;
}
