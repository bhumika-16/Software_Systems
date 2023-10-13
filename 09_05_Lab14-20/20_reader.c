/*
=====================================================================================================
Name : 20_reader.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write two programs so that both can communicate by FIFO - Use one way communication.
Date: 5th Sept, 2023.
=====================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
    const char *fifo_path = "myfifo";
    char buffer[100];

    // Open the FIFO for reading
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read data from the FIFO
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received data and print it
    buffer[bytes_read] = '\0';
    printf("Received text from FIFO file: %s\n", buffer);

    close(fd);
    return 0;
}
