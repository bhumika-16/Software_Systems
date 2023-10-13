/*
===============================================================================
Name : 27e.c
Author : Bhumika Jindal
Description : Write a program to execute ls -Rl by the following system calls
			e. execvp
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    // Using execvp to execute 'ls -Rl'
    printf("Using execvp:\n");
    char *argv[] = {"ls", "-Rl", NULL};
    execvp(argv[0], argv);
    perror("execvp");
    exit(1);

    return 0;
}
