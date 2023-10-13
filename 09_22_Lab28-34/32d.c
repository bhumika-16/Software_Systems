/*
===========================================================================================
Name : 32d.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to implement semaphore to protect any critical section.
			d. remove the created semaphore
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
};

int main() {
    int semid;
    key_t key;
    struct sembuf semOp;
    char data[1000];

    // Generate a unique key for the semaphore
    key = ftok(".", 's');
    // Create the semaphore with a single semaphore in the set
    if ((semid = semget(key, 1, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore to 1 (unlocked)
    union semun arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    // Open a file for reading
    int fd = open("filee.txt", O_RDONLY|O_CREAT, 0777);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Lock the semaphore
    semOp.sem_num = 0;
    semOp.sem_flg = SEM_UNDO;
    semOp.sem_op = -1;
    if (semop(semid, &semOp, 1) == -1) {
        perror("semop");
        exit(1);
    }

    // Read from the file
    int nread = read(fd, data, sizeof(data));
    write(1, data, nread);
    // Unlock the semaphore
    semOp.sem_op = 1;
    if (semop(semid, &semOp, 1) == -1) {
        perror("semop");
        exit(1);
    }
    // Close the file
    close(fd);
    printf("Semaphore created!! Read contents from the file...\n");
    printf("Press enter key to remove the semaphore! ");
    getchar();
    // Remove the semaphore set
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        exit(1);
    }	
    printf("Semaphore set removed successfully.\n");
    return 0;
}
