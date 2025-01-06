
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(){

  MPI_Init(NULL,NULL);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int number=0 ; 
if(rank == 0){
number =100 ;
MPI_Send(&number,1,MPI_INT,1,0,MPI_COMM_WORLD);

printf("rank %d sent number %d to process 1\n",rank , number );


MPI_Recv(&number,1,MPI_INT,1,0,MPI_COMM_WORLD , MPI_STATUS_IGNORE);

printf("rank %d received number %d from process 0\n",rank ,number);


}

if(rank == 1){

number =200 ;

MPI_Send(&number,1,MPI_INT,0,0,MPI_COMM_WORLD);

printf("rank %d sent number %d to process 0\n",number );

MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD , MPI_STATUS_IGNORE);

printf("rank %d received number %d from process 1\n",number);


}

  MPI_Finalize();

  return 0;
}
