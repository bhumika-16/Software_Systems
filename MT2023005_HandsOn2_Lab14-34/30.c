/*
===========================================================================================
Name : 30.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a shared memory.
			a. write some data to the shared memory
			b. attach with O_RDONLY and check whether you are able to overwrite.
			c. detach the shared memory
			d. remove the shared memory
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
#include <signal.h>
#define SHM_SIZE 1024

int shm_id;
void *shm_ptr;
    
// Signal handler function to catch segmentation faults
void segfault_handler(int signum) 
{
	printf("Segmentation fault handled using custom signal handler...\n");
    // Detach the shared memory segment if it's attached
    if (shm_ptr != NULL)
        shmdt(shm_ptr);
    printf("4. Detaching the shared memory...\n");

    // Remove the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        exit(1);
    }
    printf("5. Removing the shared memory...\n");
    printf("Segmentation fault caught when attempting to overwrite. Exiting...\n");
    exit(1);
}

int main() 
{
    key_t key = ftok(".", 'b'); // Create a key for the shared memory segment

	// Register the signal handler for segmentation faults
    signal(SIGSEGV, segfault_handler);
    
    // Create a shared memory segment of size 1024 bytes
    if ((shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0744)) == -1) {
        perror("shmget");
        exit(1);
    }

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
    printf("1. Message written in shared memory...\n");

    // Detach the shared memory segment from the process
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
    printf("2. Detaching the shared memory...\n");

    // Re-attach with read-only permission (O_RDONLY)
    if ((shm_ptr = shmat(shm_id, NULL, SHM_RDONLY)) == (void *)-1) {
        perror("shmat (O_RDONLY)");
        exit(1);
    }
	printf("3. Attach with O_RDONLY and checking whether we are able to overwrite...\n");
    // Try to overwrite data (This will generate a segmentation fault)
    strncpy((char *)shm_ptr, "Attempt to overwrite!", SHM_SIZE);
    return 0;
}
