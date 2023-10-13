/*
===========================================================================================
Name : 32_create_ticket.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to implement semaphore to protect any critical section.
			a. rewrite the ticket number creation program using semaphore
			b. protect shared memory from concurrent write access
			c. protect multiple pseudo resources ( may be two) using counting semaphore
			d. remove the created semaphore
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>

int main()
{
   	struct tic
   	{
   		int ticket_no;
   	};
   	struct tic *ticket;
   	
   	//Generating the key and creating the shared memory
  	int key,shmid,n;
   	key=ftok(".",'d');
   	shmid=shmget(key,sizeof(ticket),IPC_CREAT|0744);
   	
   	//writing data into shared memory
   	ticket=(struct tic*)shmat(shmid,0,0);
   	printf("Enter the initial ticket no. in the shared memory: ");
   	scanf(" %d",&n);
   	
   	//Initialising the ticket number and Displaying it
   	ticket->ticket_no=n;
   	printf("Current ticket No. is set to: %d\n",ticket->ticket_no); 
   	return 0;
}
