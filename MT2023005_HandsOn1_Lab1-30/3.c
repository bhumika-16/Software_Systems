/*
=====================================================================================
Name : 3.c
Author : Bhumika Jindal
Description : Write a program to create a file and print the file descriptor value. 
			Use creat ( ) system call
Date: 11th Aug, 2023.
=====================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Create a file named "example.txt" with read-write permissions (0666)
    int fileDescriptor = creat("example.txt", 0666);

    if (fileDescriptor == -1) {
        perror("Error creating the file");
        return 1;
    }

    printf("File created successfully with file descriptor: %d\n", fileDescriptor);
    // Close the file
    close(fileDescriptor);

    return 0;
}
