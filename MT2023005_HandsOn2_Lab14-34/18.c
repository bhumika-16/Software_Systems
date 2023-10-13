/*
=================================================================================
Name : 18.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to find out total number of directories on the pwd.
			Execute ls -l | grep ^d | wc ? Use only dup2.
Date: 5th Sept, 2023.
=================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{   
    int fd1[2], fd2[2];  //2 arrays of size 2   
    pipe(fd1); // using pipe for inter-process communication
  	pipe(fd2);
  	
  	//This child only used for writing output of "ls -l" to pipe1 write-end = STDOUT
    if(!fork())
    {   
    	dup2(fd1[1],1); //Replace STDOUT by write-end of pipe1 = New STDOUT
        close(fd1[0]); 
        close(fd2[0]); 
        close(fd2[1]); 
        execlp("ls","ls","-l",(char*) NULL);
        //exelcp() will write output of "ls -l" to write-end of the pipe
    }
    else
    {   
    	//This child is responsible for running "ls -Rl | grep ^d" command
    	//where input is received from read-end of pipe1 = STDIN and
    	//output is written to write-end of pipe2 = STDOUT
    	if(!fork())
    	{    
    		dup2(fd2[1],1);
    		dup2(fd1[0],0);
		    close(fd1[1]); 
		    close(fd2[0]);  
		    execlp("grep","grep","^d",(char*) NULL); 
		}
		//This parent is responsible for running "ls -l | grep ^d | wc" command
		//where input is received from read-end of pipe2 = STDIN and
		//output is written to STDOUT
		else
		{ 
		    dup2(fd2[0],0);
		    close(fd2[1]); 
		    close(fd1[0]); 
		    close(fd1[1]); 
		    execlp("wc","wc",(char*) NULL);  
		}
    }
    return 0;
}
