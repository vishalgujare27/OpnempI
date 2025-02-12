
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define N 100000
int main(){

  MPI_Init(NULL,NULL);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int* number = (int *)malloc(sizeof(int)*N) ; 
if(rank == 0){
  for (int i = 0; i < N; i++)
        {
          number[i] = i + 1;

        }

MPI_Sendrecv_replace(number,N,MPI_INT,1,0,1,0,MPI_COMM_WORLD , MPI_STATUS_IGNORE);

printf("Process %d Send and received number \n",rank);
for (int i = N-10; i < N; i++)
        {
          printf ("%d ", number[i]);
        }
      printf ("\n");




}

if(rank == 1){

 for (int i = 0; i < N; i++)
        {
          number[i] = (i+1) * 2;
        }

MPI_Sendrecv_replace(number,N,MPI_INT,0,0,0,0,MPI_COMM_WORLD , MPI_STATUS_IGNORE);

printf("Process %d Send and received number \n",rank);


for (int i = N-10; i < N; i++)
        {
          printf ("%d ", number[i]);
        }
      printf ("\n");





} else if (rank != 0 && rank !=1){

printf("I am process %d and have nothing to do \n",rank );
}

free(number);

  MPI_Finalize();

  return 0;
}
