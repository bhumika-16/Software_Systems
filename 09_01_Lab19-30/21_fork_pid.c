//Hands on 1: Assignment No.21 - Call fork and print the parent and child process id
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>

//We have asked the parent to wait for the child to complete it's execution.
//We can ask the parent to sleep, so that child executes first (commented part in else block)
int main()
{
	int waitStatus;
	int forkOutput = fork();
    if(!forkOutput) //when fork()==0 then child process
	{
		printf("****** Child Process ******\n");
		printf("Child pid: %d\n",getpid());		
		printf("Child's Parent pid: %d\n",getppid());		
	}
	else
	{	
		//sleep(1);
		printf("****** Parent Process ******\n");
		printf("Parent pid: %d\n",getpid());
	}
	//wait need to be used so that parent waits for child to complete
	//otherwise child ppid give some different parent id
	waitpid(forkOutput, &waitStatus, 0);
	return 0;
}
