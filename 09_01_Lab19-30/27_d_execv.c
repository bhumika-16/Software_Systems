//Hands on 1: Assignment No.27 (d) - Program to execute ls -Rl by the execv system calls
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
