//Hands on 1: Assignment No.26 (OPTIONAL) - Program to execute an executable program and pass some input to it.
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    char name[256];
    printf("Enter your name: ");
    scanf("%s", name);

    // Execute an external program (e.g., "./a.out") with the entered name as an argument
    char command[512];
    snprintf(command, sizeof(command), "./a.out %s", name);

    int return_code = system(command);
    if (return_code == 0)
        printf("External program executed successfully.\n");
    else
        printf("External program execution failed.\n");
    return 0;
}
