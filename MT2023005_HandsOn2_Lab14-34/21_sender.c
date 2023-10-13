/*
=====================================================================================================
Name : 21_sender.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write two programs so that both can communicate by FIFO - Use two way communications.
Date: 15th Sept, 2023.
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
    const char *fifo_send = "fifo_send";
    const char *fifo_receive = "fifo_receive";
    char message[100];

    // Create the sending FIFO if it doesn't exist
    mkfifo(fifo_send, 0666);
    // Open the sending FIFO for writing
    int send_fd = open(fifo_send, O_WRONLY);
    if (send_fd == -1) {
        perror("open send");
        exit(EXIT_FAILURE);
    }

    // Create the receiving FIFO if it doesn't exist
    mkfifo(fifo_receive, 0666);
    // Open the receiving FIFO for reading
    int receive_fd = open(fifo_receive, O_RDONLY);
    if (receive_fd == -1) {
        perror("open receive");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter the text: ");
    scanf(" %[^\n]",message);
    // Write data to the sending FIFO
    write(send_fd, message, strlen(message));

    // Read data from the receiving FIFO
    char buffer[100];
    ssize_t bytes_read = read(receive_fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received data and print it
    buffer[bytes_read] = '\0';
    printf("Received text from FIFO file: %s\n", buffer);

    // Close FIFOs
    close(send_fd);
    close(receive_fd);

    return 0;
}
