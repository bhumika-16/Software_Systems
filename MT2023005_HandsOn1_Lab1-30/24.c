/*
===============================================================================
Name : 24.c
Author : Bhumika Jindal
Description : Write a program to create an orphan process.
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid;
	pid = fork();
	
	//Parent process exits first, leaving the child process running as an orphan.
	if(pid == 0)
	{
		printf("I am the child, my process ID is %d\n",getpid());
		printf("My parent's process ID is %d\n",getppid());
		sleep(30);
		printf("\nAfter sleep\nI am the child, my process ID is %d\n",getpid());
        printf("My parent's process ID is %d\n",getppid());
		exit(0);
	}
	else
	{
		sleep(20);
		printf("I am the parent, my process ID is %d\n",getpid());
        printf("The parent's parent, process ID is %d\n",getppid());
		printf("Parent terminates\n");
	}
    return 0;
}
