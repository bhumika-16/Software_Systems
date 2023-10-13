/*
===========================================================================================
Name : 32ab.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to implement semaphore to protect any critical section.
			a. rewrite the ticket number creation program using semaphore
			b. protect shared memory from concurrent write access
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
#include<sys/sem.h>

union semun{
	int val;
	struct semid_ds *buf;
 	unsigned short int *array;

};
struct tic{
   int ticket_no;
};

int main()
{
   	//create shared memory and intial ticket no. using 32_create_tickec.c
	struct tic *ticket;
   	//shared memory requirement
   	int key,shmid,n;
   	key=ftok(".",'d');
   
   	// semaphore requirement
   	int keysem ,semid;   
   	union semun arg;
   	keysem = ftok(".",'a');
   	semid= semget(keysem,1,0);
   
   	int choice;
   	do
	{   		
   		printf("\nEnter 1 for Read ticket no. and 2 for Update i.e. to book tickets... Any other no. to exit...\nEnter your choice: ");
   		scanf("%d",&choice);
   
	   	if(choice==1 )
	   	{
	   		if (semctl(semid,0,GETVAL))
	   		{
				shmid=shmget(key,sizeof(ticket),0);   
   				ticket=(struct tic*)shmat(shmid,0,SHM_RDONLY);
   				printf("Current (Last Booked) tickect No: %d\n",ticket->ticket_no);
  			}
  			else
  				printf("Please wait! Other user is writing...\n"); 
 		} 
 		else if(choice==2)
   		{
			struct sembuf semOp; // Defines the operation on the semaphore
			semOp.sem_num = 0;
			semOp.sem_flg = SEM_UNDO;	
			semOp.sem_op = -1;
			semop(semid, &semOp, 1);			
			shmid=shmget(key,sizeof(ticket),0);
			ticket=(struct tic*)shmat(shmid,0,0);
			
			printf("Current ticket No: %d\n",ticket->ticket_no);
			int curr= ticket->ticket_no;
			printf("Enter no. of tickets to book: ");
			scanf("%d",&n);
			if(n<=0)
				printf("No. of tickets to book must be positive!\n");
			else
			{
				ticket->ticket_no+=n;
				printf("New ticket No: %d\n",ticket->ticket_no);
			}		   
			semOp.sem_op = 1;
			semop(semid, &semOp, 1);
			printf("Critical section is now unlocked!\n");
		}
  		else
  			printf("Invalid choice!! Program Exiting...\n");
 	}while(choice==1 || choice==2);
 	return 0;
}
