/*
===============================================================================================
Name : 15.c
Author : Bhumika Jindal
Description : Write a program to display the environmental variable of the user (use environ).
Date: 25th Aug, 2023.
===============================================================================================s
*/

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
