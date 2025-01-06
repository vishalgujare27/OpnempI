
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(){

  MPI_Init(NULL,NULL);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int sendBuf , recvBuf ; 
if(rank == 0){
sendBuf =100 ;
MPI_Sendrecv(&sendBuf,1,MPI_INT,1,0,&recvBuf , 1,MPI_INT,1,0,MPI_COMM_WORLD , MPI_STATUS_IGNORE);

printf("Process 0 Send %d received number %d from process1 \n",sendBuf , recvBuf);


}

if(rank == 1){

sendBuf =200 ;

MPI_Sendrecv(&sendBuf,1,MPI_INT,0,0,&recvBuf , 1,MPI_INT,0,0,MPI_COMM_WORLD , MPI_STATUS_IGNORE);

printf("Process 0 Send %d received number %d from process1 \n",sendBuf , recvBuf);


} else {

printf("I am process %d and have nothin to do \n",rank );
}

  MPI_Finalize();

  return 0;
}
