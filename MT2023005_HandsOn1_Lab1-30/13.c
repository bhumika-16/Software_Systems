/*
====================================================================================
Name : 13.c
Author : Bhumika Jindal
Description : Write a program to wait for a STDIN for 10 seconds using select. 
			Write a proper print statement to verify whether the data is available 
			within 10 seconds or not (check in $man 2 select).
Date: 25th Aug, 2023.
====================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    fd_set read_fds;
    struct timeval timeout;

    // Clear the set
    FD_ZERO(&read_fds);
    // Add stdin (file descriptor 0) to the set
    FD_SET(0, &read_fds);
    // Set the timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input from stdin for up to 10 seconds...\n");
    // Use select to wait for input
    int ready = select(1, &read_fds, NULL, NULL, &timeout);
    if (ready == -1) 
    {
        perror("Error in select");
        return 1;
    } 
    else if (ready == 0)
        printf("No data received within 10 seconds.\n");
    else
      	if (FD_ISSET(0, &read_fds)) //Not Required
            printf("Data is available within 10 seconds!\n");

    return 0;
}
