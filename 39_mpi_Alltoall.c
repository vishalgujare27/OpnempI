//implementing MPI_Alltoall()

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(){

  MPI_Init(NULL,NULL);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int *send_data = (int*)malloc(size*sizeof(int));
  int *recv_data = (int*)malloc(size*sizeof(int));

  for(int i=0; i<size; i++){
    send_data[i] = rank + i*10;
  }

  printf("Process %d send data: ",rank);
  for(int i=0; i<size; i++){
    printf("%d ",send_data[i]);
  }
  printf("\n");

  MPI_Alltoall(send_data, 1, MPI_INT, recv_data, 1, MPI_INT, MPI_COMM_WORLD);

  printf("Process %d received data: ",rank);
  for(int i=0; i<size; i++){
    printf("%d ",recv_data[i]);
  }
  printf("\n");

  free(send_data);
  free(recv_data);
  MPI_Finalize();

  return 0;
}
