/*
===============================================================================
Name : 29.c
Author : Bhumika Jindal
Description : Write a program to get scheduling policy and modify the 
			scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 1st Sept, 2023.
===============================================================================
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main() {
    int policy;
    struct sched_param param;

    // Get the current scheduling policy
    pid_t pid = getpid();  // Get the PID of the current process
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    // Print the current scheduling policy
    switch (policy) 
    {
        case SCHED_FIFO:
            printf("Current scheduling policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Current scheduling policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Current scheduling policy: SCHED_OTHER\n");
            break;
        default:
            printf("Unknown scheduling policy\n");
            break;
    }

    int ch;
    printf("\nEnter 1 to change the policy to SCHED_FIFO\n");
    printf("Enter 2 to change the policy to SCHED_RR\n");
    printf("Enter your choice: ");
    scanf("%d",&ch);
    printf("\n");
    if(ch!=1 && ch!=2)
    {
    	printf("Invalid choice... Scheduling Policy remains unchanged...\n");
    	exit(0);
    }
    
    // Modify the scheduling policy to SCHED_FIFO or SCHED_RR according to choice
    if(ch==1)    
    	policy = SCHED_FIFO;
    else
    	policy = SCHED_RR;
    param.sched_priority = 99;  // Set the priority (adjust as needed)

    int result = sched_setscheduler(pid, policy, &param);
    if (result == -1) {
        perror("sched_setscheduler");
        return 1;
    }

    // Verify the updated scheduling policy
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    // Print the updated scheduling policy
    switch (policy) 
    {
        case SCHED_FIFO:
            printf("Updated scheduling policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Updated scheduling policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Updated scheduling policy: SCHED_OTHER\n");
            break;
        default:
            printf("Unknown scheduling policy\n");
            break;
    }
    return 0;
}
