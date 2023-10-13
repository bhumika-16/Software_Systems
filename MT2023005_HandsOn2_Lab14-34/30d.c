/*
===========================================================================================
Name : 30d.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a shared memory.
			d. remove the shared memory
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
    void *shm_ptr;
    key_t key = ftok(".", 'b'); // Create a key for the shared memory segment
    // Create a shared memory segment of size 1024 bytes
    if ((shm_id = shmget(key, 1024, IPC_CREAT | 0744)) == -1) {
        perror("shmget");
        exit(1);
    }
  
    printf("Shared memory created. Press Enter to remove...\n");
    getchar(); // Wait for user input
    
    // Remove the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        exit(1);
    }
    printf("Shared memory removed.\n");
    return 0;
}
