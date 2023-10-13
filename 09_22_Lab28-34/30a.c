/*
===========================================================================================
Name : 30a.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a shared memory.
			a. write some data to the shared memory
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024

int main() 
{
	int shm_id;
	void *shm_ptr;
    key_t key = ftok(".", 'b'); // Create a key for the shared memory segment
    
    // Create a shared memory segment of size 1024 bytes
    if ((shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0744)) == -1) {
        perror("shmget");
        exit(1);
    }
	
	//printf("Shared memory segment created with ID: %d\n", shm_id);
    // Attach the shared memory segment to the address space of this process
    // Retrun value of shmat is pointer to start of shared memory (char* pointer)
    if ((shm_ptr = shmat(shm_id, NULL, 0)) == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    
    // Write data to the shared memory
	printf("Enter the text: ");
	scanf(" %[^\n]", (char *)shm_ptr);    
    //strncpy((char *)shm_ptr, "Hello, Shared Memory!", SHM_SIZE);
    printf("Message written in shared memory...\n");
    return 0;
}
