//Hands on 1: Assignment No. - 3
//Create a file and print the file descriptor value Using creat ( ) system call

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
