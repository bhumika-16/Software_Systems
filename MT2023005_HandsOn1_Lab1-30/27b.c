/*
===============================================================================
Name : 27b.c
Author : Bhumika Jindal
Description : Write a program to execute ls -Rl by the following system calls
			b. execlp
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    // Using execlp to execute 'ls -Rl'
    printf("Using execlp:\n");
    execlp("ls", "ls", "-Rl", (char *)NULL);
    perror("execlp");
    exit(1);
    
    return 0;
}
