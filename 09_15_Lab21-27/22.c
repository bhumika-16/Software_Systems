/*
============================================================================================
Name : 22.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to wait for data to be written into FIFO within 10 seconds, 
			use select system call with FIFO.
Date: 15th Sept, 2023.
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

int main() 
{
    const char *fifo_path = "myfifo";
    char buffer[100];

    // Create the FIFO if it doesn't exist
    mkfifo(fifo_path, 0666);
    // Open the FIFO for reading
    int fd = open(fifo_path, O_RDWR|O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    // Set up the fd_set for select
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);
    // Set the timeout value to 10 seconds
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Use select to wait for data with a timeout
    int select_result = select(fd + 1, &read_fds, NULL, NULL, &timeout);
    if (select_result == -1)
    {
        perror("select");
        exit(EXIT_FAILURE);
    } 
    else if (select_result == 0) 
    {
        // Timeout occurred, no data received within 10 seconds
        printf("Timeout: No data available/received within 10 seconds.\n");
    } 
    else 
    {
    	printf("Data is available now...\n");
        // Data is available to read
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the received data and print it
        buffer[bytes_read] = '\0';
        printf("Received Data from FIFO: %s\n", buffer);
    }

    // Close the FIFO
    close(fd);
    return 0;
}
