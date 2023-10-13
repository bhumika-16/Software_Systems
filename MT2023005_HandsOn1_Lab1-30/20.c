/*
=====================================================================================================
Name : 20.c
Author : Bhumika Jindal
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 1st Sept, 2023.
=====================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(void)
{
	printf("The priority of the current process is = %d\n",getpriority(PRIO_PROCESS,0));
	//Current priority=0 If we do nice(4), as 4>0 which means 4 is of less priority, can be done easily
	//If we do nice(-4), as -4<0 which means -4 is of high priority, so we need admin permission
	//Thus while executing this program we need sudo command to give admininistrator rights
	nice(-4);
	printf("The modified priority (using nice command) = %d\n",getpriority(PRIO_PROCESS,0));
	setpriority(PRIO_PROCESS,0,5);
	printf("The modified priority (using set priority) = %d\n",getpriority(PRIO_PROCESS,0));
	return 0;
}
