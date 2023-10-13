/*
===========================================================================================
Name : 16.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to send and receive data from parent to child vice versa. 
			Use two way communication.
Date: 5th Sept, 2023.
===========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	char buff1[80], buff2[80];
	int fd1[2], fd2[2];
	pipe(fd1);
	pipe(fd2);
	
	if(!fork()) //child
	{
		close(fd1[0]); //close the read-end of fd1 for child
		close(fd2[1]); //close the write-end of fd2 for child
		printf("Enter the message to the parent: ");
		scanf(" %[^\n]",buff1);
		write(fd1[1],buff1,sizeof(buff1));		
		read(fd2[0],buff2,sizeof(buff2));
		printf("Message from parent: %s\n", buff2);
	}
	else
	{
		close(fd1[1]); //close the write-end of fd1 for parent
		close(fd2[0]); //close the read-end of fd2 for parent
		//Child wrote into fd1 first, so read from fd1 first		
		read(fd1[0],buff1,sizeof(buff1));
		printf("Message from child: %s\n", buff1);
		printf("Enter message to child: ");
		scanf(" %[^\n]",buff2);
		write(fd2[1],buff2,sizeof(buff2));
	}
	wait(0);
	return 0;
}		
