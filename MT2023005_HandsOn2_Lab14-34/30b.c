/*
===========================================================================================
Name : 30b.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a shared memory.
			b. attach with O_RDONLY and check whether you are able to overwrite.
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
  
// Signal handler function to catch segmentation faults
void segfault_handler(int signum) 
{
    printf("Segmentation fault caught (using custom signal handler) when attempting to overwrite. Exiting...\n");
    exit(1);
}

int main() 
{
	int shm_id;
	void *shm_ptr;
    key_t key = ftok(".", 'b'); // Create a key for the shared memory segment

	// Register the signal handler for segmentation faults
    signal(SIGSEGV, segfault_handler);
    
    // Create a shared memory segment of size 1024 bytes
    if ((shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0744)) == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach with read-only permission (O_RDONLY)
    if ((shm_ptr = shmat(shm_id, NULL, SHM_RDONLY)) == (void *)-1) {
        perror("shmat (O_RDONLY)");
        exit(1);
    }
	printf("Attached with O_RDONLY and checking whether we are able to overwrite...\n");
    // Try to overwrite data (This will generate a segmentation fault)
    strncpy((char *)shm_ptr, "Attempt to overwrite!", SHM_SIZE);
    return 0;
}
