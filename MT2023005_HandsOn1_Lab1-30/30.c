/*
=========================================================================================
Name : 30.c
Author : Bhumika Jindal
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 1st Sept, 2023.
=========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int main() 
{
	time_t rawtime;
	struct tm * timeinfo;
	
	// Fork off the parent process
    int pid = fork();
    if(pid==0) //child process
    {
    	printf("Child process...\n");
    	printf("Child pid: %d\n",getpid());
    	
    	int session_id=setsid();
    	if (session_id < 0)
        	exit(EXIT_FAILURE);
    	printf("Session id: %d\n", session_id);
    	
    	// Change the current working directory to a safe place
    	chdir("/");
    	// Change the file mode mask
    	umask(0);
    	time(&rawtime);
    	timeinfo = localtime(&rawtime);
    	
    	// Specify the hour and minute when you want the script to run
        int target_hour = 11;
        int target_minute = 45;
    	while(timeinfo->tm_hour<=target_hour && timeinfo->tm_min<target_minute)
    	{
    		sleep(10);
    		time(&rawtime);
    		timeinfo = localtime(&rawtime);
    	}
    	
    	//Checking if the time is same as the specified time, then execute shell script
    	if(timeinfo->tm_hour==target_hour && timeinfo->tm_min==target_minute)
    	{
    		printf("Shell Script running...\n");
    		system("sh $HOME/Documents/GitHub/Software_Systems/09_01_Lab19-30/hello.sh");
    		//system("sh /home/bhumika/Documents/GitHub/Software_Systems/09_01_Lab19-30/hello.sh");
    		printf("Job completed successfully...\n");
    	}
    }
    else
    	printf("Parent process completed its execution\n");
   return 0;
}
