#include<stdio.h>
#include<mpi.h>

int main (int argc, char** argv){

MPI_Init(&argc , &argv );

int rank ;
MPI_Comm_rank ( MPI_COMM_WORLD,&rank );
int n = 10;
int data[n] ;
if (rank == 0){
for (int i =0 ;i<n;i++){
data[i]=i+1;
}
}

MPI_Bcast(data,n,MPI_INT,0,MPI_COMM_WORLD);
printf("rank %d : \n",rank);
for (int i =0 ;i<5;i++){
printf("%d ", data[i]);
}
 printf("\n");


MPI_Finalize(); 

return 0;
}



