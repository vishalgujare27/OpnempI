#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#define N 10000
int
main ()
{
  int size = 0, rank = 0;
  int a[N] = { 0 };
  MPI_Init (NULL, NULL);

  MPI_Comm_size (MPI_COMM_WORLD, &size);


  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  int chunk = N / size;
  int start = rank * chunk;
  int end = start + chunk;

  if (rank == size - 1)
    end = N;
  for (int i = start; i < end; i++)
    {
      a[i] = i + 1;
      //printf ("%d ", a[i]);
    }







for (int i = start; i < end; i++)
    {
      printf ("%d ", a[i]);
    }
printf("\n");
  MPI_Finalize ();

  return 0;
}
