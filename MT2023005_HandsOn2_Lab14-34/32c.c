/*
===========================================================================================
Name : 32c.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to implement semaphore to protect any critical section.
			c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// Define the number of semaphores
#define NUM_SEMAPHORES 2

int main() {
    int semid;
    key_t key;
    struct sembuf sem_op;

    // Generate a unique key for the semaphore set
    key = ftok(".", 's');

    // Create a semaphore set with NUM_SEMAPHORES semaphores
    if ((semid = semget(key, NUM_SEMAPHORES, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the two semaphores with resource counts
    unsigned short sem_init_vals[NUM_SEMAPHORES] = {1, 1}; // Initial counts

    // Set initial values for the semaphores
    if (semctl(semid, 0, SETALL, sem_init_vals) == -1) {
        perror("semctl");
        exit(1);
    }

    // Resource 1: Access using semaphore 0
    sem_op.sem_num = 0;
    sem_op.sem_op = -1; // Acquire resource 1
    sem_op.sem_flg = SEM_UNDO;

    printf("Process 1 is trying to access Resource 1...\n");
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop");
        exit(1);
    }

    printf("Process 1 has acquired Resource 1.\n");

    // Simulate working with Resource 1
    sleep(2);
    
	printf("Press enter key to exit critical section! ");
    getchar();
    printf("Process 1 is releasing Resource 1...\n");
    sem_op.sem_op = 1; // Release resource 1
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop");
        exit(1);
    }

    // Resource 2: Access using semaphore 1
    sem_op.sem_num = 1;
    sem_op.sem_op = -1; // Acquire resource 2

    printf("Process 1 is trying to access Resource 2...\n");
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop");
        exit(1);
    }

    printf("Process 1 has acquired Resource 2.\n");

    // Simulate working with Resource 2
    sleep(2);

	printf("Press enter key to exit critical section! ");
    getchar();
    printf("Process 1 is releasing Resource 2...\n");
    sem_op.sem_op = 1; // Release resource 2
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop");
        exit(1);
    }

    return 0;
}

/*
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/sem.h>
union semun{
 int val;
 struct semid_ds *buf;
 unsigned short int *array;
 
};


int main(){
struct sembuf semOp; 

// use 31_b.c to create semaphore with arg val = 2
int keysem,semid;
union semun arg;
keysem = ftok(".",'b');
semid=semget(keysem,1,0);
 char data[1000];


    int fd;
    
    fd = open("file.txt", O_RDONLY);
//locking semaphore
    semOp.sem_num = 0;
    semOp.sem_flg = SEM_UNDO;
    
    printf("Press enter to obtain lock for the critical section!\n");
    getchar();
    
    
    semOp.sem_op = -1;
    semop(semid, &semOp, 1);
    
    int nread = read(fd, &data, 1000);
    write(1,&data,nread);
    
    printf("\nPress enter key to exit critical section! ");
    getchar();

    semOp.sem_op = 1;
    semop(semid,&semOp, 1);
    
    close(fd);
    
}*/
