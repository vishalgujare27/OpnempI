#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define N 1000
int
main ()
{

  MPI_Init (NULL, NULL);

  int rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  int *number;
  int *recv ;
      number = (int *) malloc (sizeof (int) * N);
      recv = (int *) malloc (sizeof (int) * N);
  if (rank == 0)
    {

      for (int i = 0; i < N; i++)
	{
	  number[i] = i + 1;

	}

int buffer_size = MPI_BSEND_OVERHEAD + (sizeof(int)*N);
void * buffer = malloc(buffer_size);

MPI_Buffer_attach(buffer,buffer_size);




      MPI_Bsend (number, N, MPI_INT, 1, 0, MPI_COMM_WORLD);

      MPI_Recv (recv, N, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

MPI_Buffer_detach(&buffer , &buffer_size);


      printf ("rank %d after swapping from process 1\n", rank);
 for (int i = 0; i < N; i++)
        {
          number[i] =recv[i];
        }
free(recv);

      for (int i = N-10; i < N; i++)
	{
	  printf ("%d ", number[i]);
	}
      printf ("\n");
    }
  if (rank == 1)
    {
      for (int i = 0; i < N; i++)
	{
	  number[i] = (i+1) * 2;
	}

int buffer_size = MPI_BSEND_OVERHEAD + (sizeof(int)*N);
void * buffer = malloc(buffer_size);

MPI_Buffer_attach(buffer,buffer_size);




      MPI_Bsend (number, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Recv (recv, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


MPI_Buffer_detach(&buffer , &buffer_size);

      printf ("rank %d after swapping  from process 0\n", rank);

 for (int i = 0; i < N; i++)
        {
          number[i] =recv[i];
        }

free(recv);
      for (int i = N-10; i < N; i++)
	{
	  printf ("%d ", number[i]);
	}
      printf ("\n");
    }

free(number);

  MPI_Finalize ();

  return 0;
}
