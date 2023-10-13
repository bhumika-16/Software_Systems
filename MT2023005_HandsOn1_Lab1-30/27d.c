/*
===============================================================================
Name : 27d.c
Author : Bhumika Jindal
Description : Write a program to execute ls -Rl by the following system calls
			d. execv
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    // Using execv to execute 'ls -Rl'
    printf("Using execv:\n");
    char *argv[] = {"/bin/ls", "-Rl", NULL};
    execv(argv[0], argv);
    perror("execv");
    exit(1);

    return 0;
}
