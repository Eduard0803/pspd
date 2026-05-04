#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define MASTER 0
#define TAG 0

int main(int argc, char *argv[]){
    int rank, nprocs;
    char hostname[1024];


    MPI_Init(&argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);


    gethostname(hostname, sizeof(hostname));


    if(rank == MASTER){
        int N, _STOP=-1;

        printf("Digite o valor de N: ");
        scanf("%d", &N);
        printf("\n");

        int data = 0;

        printf("%d/%d - Host %s - %d\n", rank, nprocs, hostname, data);

        MPI_Send(&data, 1, MPI_INT, (rank+1)%nprocs, TAG, MPI_COMM_WORLD);
    }

    for(;;){
        int recv_data;
        MPI_Recv(&recv_data, 1, MPI_INT, rank-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("%d/%d - Host %s - %d\n", rank, nprocs, hostname, recv_data++);

        MPI_Send(&recv_data, 1, MPI_INT, (rank+1)%nprocs, TAG, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
