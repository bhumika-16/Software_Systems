/*
===========================================================================================
Name : 28.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to change the exiting message queue permission. 
			(use msqid_ds structure)
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() 
{
    int msg_queue_id;
    key_t key;
    
    // Generate a unique key for the message queue
    key = ftok("/tmp", 'B');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Open the message queue with read and write permissions (0666)
    msg_queue_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Display the initial permissions
    struct msqid_ds queue_info;
    if (msgctl(msg_queue_id, IPC_STAT, &queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Initial Permissions: 0%o\n", queue_info.msg_perm.mode);

    // Modify the permissions (e.g., change to read-only)
    queue_info.msg_perm.mode = 0444;  // Set to read-only (4)
    if (msgctl(msg_queue_id, IPC_SET, &queue_info) == -1) {
        perror("msgctl IPC_SET");
        exit(EXIT_FAILURE);
    }

    // Display the updated permissions
    if (msgctl(msg_queue_id, IPC_STAT, &queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Updated Permissions: 0%o\n", queue_info.msg_perm.mode);
    return 0;
}
