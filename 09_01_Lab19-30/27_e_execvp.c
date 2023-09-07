//Hands on 1: Assignment No.27 (e) - Program to execute ls -Rl by the execvp system calls
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
