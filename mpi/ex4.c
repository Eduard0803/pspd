#include <mpi.h>
#include <stdio.h>

#define MASTER 0
#define TAG 0

// Enviando um int[] entre N maquinas
// ----------------------------------
// Compilar: mpicc exec4.c -o main
// Executar: mpirun -np 6 ./main

int main(int argc, char *argv[]) {
    int rank, nprocs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if(rank == MASTER){
        for(int i=1, data=2; i<nprocs; ++i, data+=2)
            MPI_Send(&data, 1, MPI_INT, i, TAG, MPI_COMM_WORLD);
    }
    else{
        int rec;
        MPI_Recv(&rec, 1, MPI_INT, MASTER, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Slave %d/%d recebeu ... %d\n", rank, nprocs-1, rec);
    }

    MPI_Finalize();
    return 0;
}
