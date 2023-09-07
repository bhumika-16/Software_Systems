//Hands on 1: Assignment No.27 (b) - Program to execute ls -Rl by the execlp system calls
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
