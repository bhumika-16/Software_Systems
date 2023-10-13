/*
===============================================================================
Name : 4.c
Author : Bhumika Jindal
Description : Write a program to open an existing file with read write mode. 
			Try O_EXCL flag also.
Date: 11th Aug, 2023.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char* filename = "example.txt";
    int fd;

    // Open the file in read-write mode
    fd = open(filename, O_RDWR);

    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    } else 
        printf("File opened successfully with file descriptor: %d\n", fd);

    // Try to open the file with O_EXCL flag (should fail if the file exists)
    int fd_excl = open(filename, O_RDWR | O_EXCL);

    if (fd_excl == -1) {
        if (errno == EEXIST)
            perror("File already exists");
        else
            perror("Error opening the file with O_EXCL");
    } else {
        printf("File opened with O_EXCL successfully with file descriptor: %d\n", fd_excl);
        close(fd_excl);
    }

    // Close the file
    close(fd);
    
    return 0;
}
