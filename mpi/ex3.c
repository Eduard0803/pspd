#include <mpi.h>
#include <stdio.h>

#define MASTER 0
#define TAG 0

// enviando um int[] entre duas maquinas

int main(int argc, char *argv[]) {
    int rank, nprocs;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if(rank == MASTER){
        int x[5] = {15, 21, 23, 45, 49};
        MPI_Send(&x, 5, MPI_INT, 1, TAG, MPI_COMM_WORLD);
    }
    else{
        int rec[5];
        MPI_Recv(&rec, 5, MPI_INT, MASTER, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i=0; i<5; ++i)
            printf("Slave recebeu ... %d\n", rec[i]);
    }

    MPI_Finalize();
    return 0;
}
