//Hands on 1: Assignment No.15 - Display the environmental variable of the user using environ
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main() 
{
    char **env = environ;
    
    printf("Environmental variables:\n");    
    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
