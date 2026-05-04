#include <mpi.h>
#include<stdio.h>

#define MASTER 0
#define TAG 0

int main(int argc, char *argv[]){
    int rank, nprocs;

    MPI_Init(&argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);


    if(rank == MASTER){
        char data[1001];
        int len_data;

        printf("Digite a string para envio: ");
        scanf(" %[^\n]%n", data, &len_data);
        printf("\n");
        
        MPI_Send(&len_data, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);
        MPI_Send(data, len_data+1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD);
        
        int len_rec;
        MPI_Recv(&len_rec, 1, MPI_INT, nprocs-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        char rec[len_rec+1];
        MPI_Recv(rec, len_rec+1, MPI_CHAR, nprocs-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Master recived str: %s\n", rec);
    }
    else{
        int len_rec;
        MPI_Recv(&len_rec, 1, MPI_INT, rank-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        char rec[len_rec+1];
        MPI_Recv(rec, len_rec+1, MPI_CHAR, rank-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Slave %d/%d recived str: %s\n", rank, nprocs-1, rec);

        MPI_Send(&len_rec, 1, MPI_INT, (rank+1)%nprocs, TAG, MPI_COMM_WORLD);
        MPI_Send(rec, len_rec+1, MPI_CHAR, (rank+1)%nprocs, TAG, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
