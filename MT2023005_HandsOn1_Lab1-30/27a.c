/*
===============================================================================
Name : 27a.c
Author : Bhumika Jindal
Description : Write a program to execute ls -Rl by the following system calls
			a. execl
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    // Using execl to execute 'ls -Rl'
    printf("Using execl:\n");
    /* Each exec function accepts the command to run as the first argument, 
    followed by the command and its arguments as separate arguments. 
    The (char *)NULL or NULL is used to terminate the argument list. */    

    execl("/bin/ls", "ls", "-Rl", (char *)NULL);
    printf("Hey...\n"); //This is not executed
    perror("execl"); //This is executed when command fails
    exit(1);
    
    return 0;
}
