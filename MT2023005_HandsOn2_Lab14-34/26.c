/*
===========================================================================================
Name : 26.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to send messages to the message queue. Check $ipcs -q
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

    // Create or open the message queue
    msg_queue_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Send messages to the message queue
    printf("Enter message type: ");
    scanf("%ld",&msg.mtype);
    printf("Enter message text: ");
    scanf(" %[^\n]",msg.mtext);
    if (msgsnd(msg_queue_id, &msg, strlen(msg.mtext)+1, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Messages sent to the queue...\n");
    return 0;
 }
