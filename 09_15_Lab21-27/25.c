/*
=================================================================================================
Name : 25.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
			a. access permission
			b. uid, gid
			c. time of last message sent and received
			d. time of last change in the message queue
			d. size of the queue
			f. number of messages in the queue
			g. maximum number of bytes allowed
			h. pid of the msgsnd and msgrcv
Date: 15th Sept, 2023.
=================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() 
{
    int msg_queue_id;
    // Create or open the message queue
    key_t key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    msg_queue_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msqid_ds queue_info;
    // Retrieve information about the message queue
    if (msgctl(msg_queue_id, IPC_STAT, &queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    // Print the requested information
    printf("Access Permission: 0%o\n", queue_info.msg_perm.mode);
    printf("UID: %d\n", queue_info.msg_perm.uid);
    printf("GID: %d\n", queue_info.msg_perm.gid);
    printf("Time of Last Message Sent: %s", ctime(&queue_info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&queue_info.msg_rtime));
    printf("Time of Last Change: %s", ctime(&queue_info.msg_ctime));
    printf("Size of Queue: %ld bytes\n", (long)queue_info.msg_qbytes);
    printf("Number of Messages in Queue: %ld\n", (long)queue_info.msg_qnum);
    printf("Maximum Number of Bytes Allowed per Message: %ld\n", (long)queue_info.msg_qbytes);
    printf("PID of msgsnd (last sender): %d\n", queue_info.msg_lspid);
    printf("PID of msgrcv (last receiver): %d\n", queue_info.msg_lrpid);
    return 0;
}
