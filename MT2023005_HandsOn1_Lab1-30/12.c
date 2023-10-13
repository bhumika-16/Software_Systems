/*
==================================================================================
Name : 11.c
Author : Bhumika Jindal
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 25th Aug, 2023.
==================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> 

void print_opening_mode(int fd)
{
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Error getting file flags");
        exit(1);
    }
	printf("FCNTL Value: %d...\n",flags);
	//With the help of access mode we get the flag of the file descriptor
	//Values are O_RDONLY=0, O_WRONLY=1, O_RDWR=2
	int fflags = flags & O_ACCMODE;
    if (fflags == O_RDONLY)
        printf("File opened in Read-Only mode\n");
    else if (fflags == O_WRONLY)
        printf("File opened in Write-Only mode\n");
    else if (fflags == O_RDWR)
        printf("File opened in Read-Write mode\n");
    else
        printf("Cannot determine opening mode\n");
}

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
	printf("Invalid number of arguments...!!\n");
	return 0;
    }
    const char *file_name = argv[1];

    // Open the file in different modes
    int fd_read = open(file_name, O_RDONLY);
    int fd_write = open(file_name, O_WRONLY);
    int fd_read_write = open(file_name, O_RDWR);

    if (fd_read == -1 || fd_write == -1 || fd_read_write == -1) {
        perror("Error opening the file");
        return 1;
    }

    // Print opening modes
    printf("File: %s\n", file_name);
    printf("Descriptor %d:\n", fd_read);
    print_opening_mode(fd_read);

    printf("\nDescriptor %d:\n", fd_write);
    print_opening_mode(fd_write);

    printf("\nDescriptor %d:\n", fd_read_write);
    print_opening_mode(fd_read_write);

    // Close the file descriptors
    close(fd_read);
    close(fd_write);
    close(fd_read_write);

    return 0;
}
