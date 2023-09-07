//Hands on 1: Assignment No.27 (a) - Program to execute ls -Rl by the execl system calls
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
