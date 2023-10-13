/*
=====================================================================================================
Name : 20_writer.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write two programs so that both can communicate by FIFO - Use one way communication.
Date: 5th Sept, 2023.
=====================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
    const char *fifo_path = "myfifo";
    char message[100];

    // Create the FIFO (named pipe) if it doesn't exist
    mkfifo(fifo_path, 0666);

    // Open the FIFO for writing
    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

	printf("Enter the text: ");
	scanf(" %[^\n]", message);
    // Write data to the FIFO
    write(fd, message, sizeof(message));
    
    close(fd);
    return 0;
}
