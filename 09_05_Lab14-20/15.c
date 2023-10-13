/*
===========================================================================================
Name : 15.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a simple program to send some data from parent to the child process.
Date: 5th Sept, 2023.
===========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	char buff[80];
	int fd[2];
	pipe(fd);
	
	int pid=fork();
	
	//Child process because fork() return value zero
	//Child should be reading
	if(pid==0)
	{
		close(fd[1]); //Closing the write end of pipe for child
		read(fd[0],buff,sizeof(buff));
		printf("Message from parent to the child process: %s\n",buff);
	}
	
	//Parent process because fork() return value non-zero
	//Parent should be writing
	else
	{
		close(fd[0]); //closing the read end of pipe for parent
		printf("Enter the message to the parent: ");
		scanf(" %[^\n]",buff); //Read till newline encountered
		write(fd[1],buff,sizeof(buff));
	}
	wait(0); //Wait till all children have terminated
	return 0;
}		
