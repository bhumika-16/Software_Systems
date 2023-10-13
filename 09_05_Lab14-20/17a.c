/*
=================================================================================
Name : 17a.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to execute ls -l | wc.
			a. use dup
Date: 5th Sept, 2023.
=================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  
    // array of 2 size: fd[0] is for reading and fd[1] is for writing over a pipe    
    int fd[2];     
    pipe(fd); // using pipe for inter-process communication
  
    if(!fork())
    {        
        close(1); //close normal STDOUT
        close(fd[0]); //close reading part of pipe in child
        dup(fd[1]); //Duplicate fd[1] to the lowest fd value available = 1
        execlp("ls","ls","-l",(char*) NULL);
        //exelcp() will write output of "ls -l" to write-end of the pipe
    }
    else
    {        
        close(0); //close normal STDIN
        close(fd[1]);  //close writing part of pipe in parent
        dup(fd[0]); //Duplicate fd[0] to the lowest fd value available = 1
        execlp("wc","wc",(char*) NULL);  
        //execlp() will read input from read end of pipe as input to "wc"
        //command an show the output to the fd with value 1 i.e. STDOUT
    }
    return 0;
}
