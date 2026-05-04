#include <mpi.h>
#include <stdio.h>

#define MASTER 0
#define TAG 0

// enviando um int entre duas maquinas

int main(int argc, char *argv[]) {
    int rank, nprocs;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if(rank == MASTER){
        int x = 10;
        MPI_Send(&x, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Master recebeu ... %d\n", x);
    }
    else{
        int rec;
        MPI_Recv(&rec, 1, MPI_INT, MASTER, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Slave recebeu ... %d\n", rec);
        rec *= 2;
        MPI_Send(&rec, 1, MPI_INT, MASTER, TAG, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
