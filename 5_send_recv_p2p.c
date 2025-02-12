#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#define N 10000
int
main (int argc, char **argv)
{
  int myid, size;
  int myval;
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &size);


  MPI_Comm_rank (MPI_COMM_WORLD, &myid);


  if (myid == 0)
    {
      myval = 100;
   for(int i =1;i<size;i++){
      printf ("\nmyid: %d \t myval = %d", myid, myval);
      MPI_Send (&myval, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      printf ("\n\tData sent.\t\n", myid);
}    
}
  else
    {
      myval = 200;
      MPI_Recv (&myval, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf ("\nmyid: %d \t DATA received . ", myid);

      printf ("\nmyid: %d \t myval = %d", myid, myval);
    }







  MPI_Finalize ();

  return 0;
}
