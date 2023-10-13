/*
===============================================================================
Name : 28.c  (OPTIONAL)
Author : Bhumika Jindal
Description : Write a program to get maximum and minimum real time priority.
Date: 1st Sept, 2023.
===============================================================================
*/

#include <stdio.h>
//header to use the scheduling functions
#include <sched.h>

int main() 
{
    int max_priority, min_priority;

    //Get the maximum real-time priority
    //The SCHED_FIFO policy is one of the real-time scheduling policies.
    max_priority = sched_get_priority_max(SCHED_FIFO);
    if (max_priority == -1) 
    {
        perror("sched_get_priority_max");
        return 1;
    }

    //Get the minimum real-time priority
    min_priority = sched_get_priority_min(SCHED_FIFO);
    if (min_priority == -1) 
    {
        perror("sched_get_priority_min");
        return 1;
    }

    printf("Maximum real-time priority: %d\n", max_priority);
    printf("Minimum real-time priority: %d\n", min_priority);
    return 0;
}
