/*
===========================================================================================
Name : 30c.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a shared memory.
			c. detach the shared memory
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() 
{
    int shm_id;
    // Attach the shared memory segment
    if ((shm_id = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the address space of this process
    void *shm_ptr;
    if ((shm_ptr = shmat(shm_id, NULL, 0)) == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Attached to shared memory. Press Enter to detach...\n");
    getchar(); // Wait for user input
    // Detach the shared memory segment from the process
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
    printf("Shared memory detached.\n");
    return 0;
}
