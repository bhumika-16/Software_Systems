/*
=====================================================================================================
Name : 21_receiver.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write two programs so that both can communicate by FIFO - Use two way communications.
Date: 15th Sept, 2023.
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
    const char *fifo_send = "fifo_send";
    const char *fifo_receive = "fifo_receive";
    char buffer[100], message[100];

    // Open the sending FIFO for writing
    int send_fd = open(fifo_send, O_RDONLY);
    if (send_fd == -1) {
        perror("open send");
        exit(EXIT_FAILURE);
    }

    // Open the receiving FIFO for reading
    int receive_fd = open(fifo_receive, O_WRONLY);
    if (receive_fd == -1) {
        perror("open receive");
        exit(EXIT_FAILURE);
    }

    // Read data from the sending FIFO
    ssize_t bytes_read = read(send_fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received data and print it
    buffer[bytes_read] = '\0';
    printf("Received text from FIFO file: %s\n", buffer);

    // Write data to the receiving FIFO
    printf("Enter the text: ");
    scanf(" %[^\n]",message);
    write(receive_fd, message, sizeof(message));

    // Close FIFOs
    close(send_fd);
    close(receive_fd);

    return 0;
}
