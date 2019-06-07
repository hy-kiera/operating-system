#include <stdio.h>
#include <unistd.h>

int main(void){
	int i;
	for(i = 0; i < 3; i++){
		fork();
		printf("i : %d , %d \n", i, getpid());
	}
	return 0;
}
