/*
=================================================================================================
Name : 24.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a message queue and print the key and message queue id.
Date: 15th Sept, 2023.
=================================================================================================
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
    // 'a'=ASCII value of "a" given as proj_id and "." will be string used to create key
    key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create the message queue with read and write permissions (0666)
    msg_queue_id = msgget(key, IPC_CREAT | IPC_EXCL | 0744);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    
	//%0x for Hexadecimal value
    printf("Message Queue Key: 0x%0x\t", key);
    printf("Message Queue ID: %d\n", msg_queue_id);
    return 0;
}
