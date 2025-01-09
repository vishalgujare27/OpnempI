#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc,char** argv){
MPI_Init(&argc,&argv);
int rank,size;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);

int color = rank % 3;
MPI_Comm new_comm;
MPI_Comm_split(MPI_COMM_WORLD,color,rank,&new_comm);

int new_rank,new_size;
MPI_Comm_rank(new_comm,&new_rank);
MPI_Comm_size(new_comm,&new_size);

printf("world rank %d ,new rank %d new size : %d\n",rank,new_rank,new_size);

int send_data = new_rank;
int recv_data;
MPI_Allreduce(&send_data,&recv_data,1,MPI_INT,MPI_SUM,new_comm);
printf("world rank : %d, new comm sum : %d\n",rank,recv_data);

MPI_Comm_free(&new_comm);
MPI_Finalize();

return 0;
}

