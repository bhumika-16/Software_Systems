//Hands on 1: Assignment No.27 (c) - Program to execute ls -Rl by the execle system calls
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
