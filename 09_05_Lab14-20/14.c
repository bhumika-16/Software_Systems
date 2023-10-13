/*
===============================================================================
Name : 14.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a simple program to create a pipe, write to the pipe, 
			read from pipe and display on the monitor.
Date: 5th Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i,j,fd[2];
	char buf[10];
	i = pipe(fd); //Returns 0 on success and -1 on failure
	printf("Return value for Pipe: %d\n",i);
	j = write(fd[1],"Hello...\n",10);
	printf("Writing to the pipe completed...\n");
	
	read(fd[0],buf,sizeof(buf));
	printf("Data read from Pipe: %s\n",buf);
	return 0;
}
