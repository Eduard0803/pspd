#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define MASTER 0
#define TAG 0

int main(int argc, char *argv[]){
    int rank, nprocs;
    char hostname[1024];

    int N, _STOP=-1, data;


    MPI_Init(&argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);


    gethostname(hostname, sizeof(hostname));


    if(rank == MASTER){
        data=0;

        printf("Digite o valor de N: ");
        scanf("%d", &N);
        printf("\n");

        // for(int i=1; i<nprocs; ++i)
        //     MPI_Send(&N, 1, MPI_INT, i, TAG, MPI_COMM_WORLD);

        printf("%d/%d - Host %s - %d\n", rank, nprocs, hostname, data++);

        MPI_Send(&data, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);

        while(1){
            MPI_Recv(&data, 1, MPI_INT, nprocs-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d/%d - Host %s - %d\n", rank, nprocs, hostname, data++);
            if(data > N){
                MPI_Send(&_STOP, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);
                break;
            }
            MPI_Send(&data, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);
        }
    }
    else{
        // MPI_Recv(&N, 1, MPI_INT, rank-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // printf("%d/%d - Host: %s - N=%d\n", rank, nprocs, hostname, N);

        MPI_Recv(&data, 1, MPI_INT, rank-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("%d/%d - Host %s - %d\n", rank, nprocs, hostname, data++);

        MPI_Send(&data, 1, MPI_INT, (rank+1)%nprocs, TAG, MPI_COMM_WORLD);
    
        for(;;){
            MPI_Recv(&data, 1, MPI_INT, rank-1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if(data == _STOP){
                MPI_Send(&_STOP, 1, MPI_INT, (rank+1)%nprocs, TAG, MPI_COMM_WORLD);
                break;
            }

            printf("%d/%d - Host %s - %d\n", rank, nprocs, hostname, data++);

            MPI_Send(&data, 1, MPI_INT, (rank+1)%nprocs, TAG, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
