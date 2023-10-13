/*
=======================================================================================
Name : 23.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to print the maximum number of files can be opened 
			within a process and size of a pipe (circular buffer).
Date: 15th Sept, 2023.
=======================================================================================
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() 
{
    // Get the maximum number of files that can be opened by this process
    struct rlimit rlim;
    if (getrlimit(RLIMIT_NOFILE, &rlim) == 0)
        printf("Maximum number of files that can be opened by this process: %ld\n", rlim.rlim_cur);
    else {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    // Create a pipe to get its buffer size
    int pipe_fd[2];
    if (pipe(pipe_fd) == 0) 
    {
        int pipe_buf_size = fcntl(pipe_fd[0], F_GETPIPE_SZ);
        if (pipe_buf_size != -1)
            printf("Size of a pipe (circular buffer): %d bytes\n", pipe_buf_size);
        else
            perror("fcntl");
    }else {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    return 0;
}
