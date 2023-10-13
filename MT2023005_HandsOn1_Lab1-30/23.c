/*
===============================================================================
Name : 23.c
Author : Bhumika Jindal
Description : Write a program to create a Zombie state of the running program.
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Child becomes Zombie as parent is sleeping when child process exits.
int main()
{
    //Fork returns process id in parent process
    pid_t child_pid = fork();
  
    //Child process 
    if(child_pid==0)
    {
        printf("In child process, PID = %d\n", getpid());        
        sleep(2); // Simulate some work in the child process
        printf("Child Process is exiting...\n");
        exit(0);
    } 
     
    //Parent process
    else        
    {
    	printf("This is parent process %d\n", getpid());
    	printf("Parent goes to Sleep...\n");
    	//The parent process does not explicitly wait for the child process 
    	//to complete using wait, which is why the child becomes a zombie.
    	sleep(30);// Sleep for a while to allow the child process to complete
    	printf("Parent wakes up... and exits...!!\n");
    	//wait(0); //Used for removal of zombie process
    }
  
    return 0;
}
