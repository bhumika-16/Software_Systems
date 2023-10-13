/*
===============================================================================
Name : 25.c
Author : Bhumika Jindal
Description : Write a program to create three child processes. The parent 
			should wait for a particular child (use waitpid system call).
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pids[3]; // Array to store child process IDs

    // Create three child processes
    for (int i = 0; i < 3; i++)
    {
        child_pids[i] = fork();
        if (child_pids[i] == -1) 
        {
            perror("fork");
            return 1;
        }

        if (child_pids[i] == 0) 
        {
            // This code is executed by the child process
            printf("Child process %d (PID %d) is running.\n", i + 1, getpid());
            sleep(2 + i); // Simulate some work
            printf("Child process %d (PID %d) is exiting.\n", i + 1, getpid());
            exit(0);
        }
    }

    // Parent process
    int status;
    pid_t waited_pid;

    // Wait for a specific child (e.g., the second child with index 1)
    waited_pid = waitpid(child_pids[1], &status, 0);
    if (waited_pid == -1) 
    {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status)) 
    {
        printf("Parent process: Child %d (PID %d) has exited with status %d.\n",2, waited_pid, WEXITSTATUS(status));
    }

    return 0;
}
