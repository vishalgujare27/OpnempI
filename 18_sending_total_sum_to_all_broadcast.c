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

int totalsum = 0 ;
  if (rank == 0)
    {
      int localsum = 0;
      for (int i = 1; i < size; i++)
	{

	  MPI_Recv (&localsum, 1, MPI_INT, i, 0, MPI_COMM_WORLD,
		    MPI_STATUS_IGNORE);
	  totalsum += localsum;
	}
    }

if ( rank != 0){
      MPI_Send (&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
      MPI_Bcast (&totalsum, 1, MPI_INT, 0, MPI_COMM_WORLD);
  printf(" Rank : %d  : Sum : %d \n",rank,totalsum);  
  MPI_Finalize ();
  return 0;
}
