/*
===========================================================================================
Name : 31a.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a semaphore and initialize value to the semaphore.
			a. create a binary semaphore
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main() 
{
    int binarySemaphore;
    key_t key = ftok("/tmp", 'S'); // Create a key for the semaphore

    // Create a binary semaphore
    if ((binarySemaphore = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
        perror("semget (binary)");
        exit(1);
    }

    // Initialize the binary semaphore to 1
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
        struct seminfo *__buf;
    } semopts;

    semopts.val = 1;
    if (semctl(binarySemaphore, 0, SETVAL, semopts) == -1) {
        perror("semctl (SETVAL)");
        exit(1);
    }
    printf("Binary semaphore created and initialized.\n");
    return 0;
}
