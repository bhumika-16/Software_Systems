/*
===============================================================================
Name : 27c.c
Author : Bhumika Jindal
Description : Write a program to execute ls -Rl by the following system calls
			c. execle
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    // Using execle to execute 'ls -Rl'
    printf("Using execle:\n");
    //For execle, we also provide an array of environment variables, which we set to NULL here
    char *envp[] = {NULL};
    execle("/bin/ls", "ls", "-Rl", (char *)NULL, envp);
    perror("execle");
    exit(1);

    return 0;
}
