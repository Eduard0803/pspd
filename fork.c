#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 1000

int main(){
	int v[MAX];
	int pid, sum=0, start, end;

	for(int i=0; i<MAX; ++i)
		v[i] = 1;

	pid = fork();

	if(pid == 0){
		start = MAX/2;
		end = MAX;
	}
	else{
		start = 0;
		end = MAX/2;
	}

	for(int i=start; i<end; ++i)
		sum += v[i];


	printf("SOMA = %d\n", sum);

	return 0;
}
