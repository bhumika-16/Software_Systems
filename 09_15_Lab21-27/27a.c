/*
===========================================================================================
Name : 27a.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to receive messages from the message queue.
			a. with 0 as a flag
Date: 15th Sept, 2023.
===========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSG_SIZE 256

struct message {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() 
{
    int msg_queue_id;
    key_t key;
    struct message msg;

    // Generate a unique key for the message queue
    key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Open the message queue
    msg_queue_id = msgget(key, 0);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

	printf("Enter message type: ");
	scanf("%ld",&msg.mtype);
    // Receive a message with no flags (blocking)
    int ret = msgrcv(msg_queue_id, &msg, sizeof(msg.mtext), msg.mtype, 0);
    if(ret == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    printf("Received message with no flags (blocking):\n");
    printf("Type: %ld\t", msg.mtype);
    printf("Content: %s\n", msg.mtext);
    return 0;
}
