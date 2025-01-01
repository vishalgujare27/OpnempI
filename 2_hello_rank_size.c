#include<stdio.h>
#include<unistd.h>
#include<mpi.h>

int main () {
 int size , rank ; 
MPI_Init(NULL,NULL);

MPI_Comm_size(MPI_COMM_WORLD,&size);

MPI_Comm_rank(MPI_COMM_WORLD,&rank);
printf("Hello WOrld from process %d of %d \n",rank,size);

MPI_Finalize();
return 0;
 }


