
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(){

  MPI_Init(NULL,NULL);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int number ; 
if(rank == 0){
number =100 ;
MPI_Sendrecv_replace(&number,1,MPI_INT,1,0,1,0,MPI_COMM_WORLD , MPI_STATUS_IGNORE);

printf("Process 0 Send and received number %d  \n",number);


}

if(rank == 1){
number =200 ;
MPI_Sendrecv_replace(&number,1,MPI_INT,0,0,0,0,MPI_COMM_WORLD , MPI_STATUS_IGNORE);

printf("Process 1 Send and received number %d  \n",number);


} else {

printf("I am process %d and have nothing to do \n",rank );
}

  MPI_Finalize();

  return 0;
}
