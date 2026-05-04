#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define N_PROCESS 7

int main(){
    int v[] = {15, 21, 23, 26, 45, 49};
    int TAM = sizeof(v) / sizeof(v[0]),
        CHUNCK = TAM/N_PROCESS;

    // printf("TAM = %d\n", TAM);
    // printf("N_PROCESS = %d\n", N_PROCESS);
    // printf("CHUNCK = %d\n", CHUNCK);

    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666),
        *total_sum = (int *) shmat(shmid, NULL, 0);
    *total_sum = 0;

    for(int i=0; i<N_PROCESS; ++i){
        if(fork() == 0){
            int start = i*CHUNCK, 
                end=(i+1)*CHUNCK,
                count = 0;
            
            if(i == N_PROCESS-1)
                end = TAM;

            for(int k=start; k<end; ++k)
                count += v[k];
            *total_sum += count;
            shmdt(total_sum);   
            printf("PPID: %d --- PID: %d --- S: %d --- E: %d --- COUNT = %d --- I: %d\n", getppid(), getpid(), start, end, count, i);
            exit(0);
        }
    }

    for(int i=0; i<N_PROCESS; ++i)
        wait(NULL);

    printf("SOMA = %d\n", *total_sum);

    shmdt(total_sum);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
