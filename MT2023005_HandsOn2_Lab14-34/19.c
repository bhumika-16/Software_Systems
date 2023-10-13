/*
===========================================================================================
Name : 19.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Create a FIFO file by
			a. mknod command
			b. mkfifo command
			c. use strace command to find out, which command (mknod or mkfifo) is better.
			c. mknod system call
			d. mkfifo library function
Date: 5th Sept, 2023.
============================================================================================
*/

//Part a,b,c done in terminal (Shown in Screenshot)
//strace displays the execution process in sequence with each system call
//mkfifo actually calls mknod() - System call, So mknod() is faster always

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
	//Creating FIFO using mknod system call
    if (mknod("myfifo_1", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }
   	printf("FIFO named myfifo_1 created using mknod command...\n");
   	
   	//Creating FIFO using mkfifo library function
   	if (mkfifo("myfifo_2", 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    printf("FIFO named myfifo_2 created using mkfifo command...\n");
    return 0;
}
