/*
===========================================================================================
Name : 29.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to remove the message queue.
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

    // Generate a unique key for the message queue (use the same key you used to create it)
    key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Open the message queue
    msg_queue_id = msgget(key, 0666);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Remove the message queue
    if (msgctl(msg_queue_id, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully.\n");
    return 0;
}
