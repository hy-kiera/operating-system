#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 5

int nums[SIZE] = {0,1,2,3,4};

int main(void){
	int i;
	pid_t pid;

	pid = fork();

	if (pid == 0){
		for (i = 0; i < SIZE; i++){
			nums[i] *= -i;
			printf("i: %d, CHILD: %d\n", i, nums[i]);
		}
	}
	else if (pid > 0){
		wait(NULL);
		for (i = 0; i < SIZE; i++)
			printf("i: %d, PARENT: %d\n", i, nums[i]);
	}
	return 0;
}
