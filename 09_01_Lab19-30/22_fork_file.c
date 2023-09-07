//Hands on 1: Assignment No.22 - Open a file, call fork, and then write to the file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
	printf("Invalid number of arguments...!!\n");
	return 0;
    }
    
    const char *file_name = argv[1];    
	//Open the file
	//int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//If we remove  O_APPEND then the old content is lost & file is re-written
    int fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    
    // Fork to create a child process
    pid_t child_pid = fork();  //fork() returns pid of newly created child process
    if (child_pid == -1) {
        perror("Error in doing fork");
        return 1;
    }
    
    if(child_pid == 0)
    {
    	// This code is executed by the child process
        const char* child_message = "Child process writing to the file...\nHello! I am a child process.\n";
        write(fd, child_message, strlen(child_message));
    }
    else
    {
    	// This code is executed by the parent process
        const char* parent_message = "Parent process writing to the file...\nHave a good day...!!\n";
        write(fd, parent_message, strlen(parent_message));

        // Wait for the child process to finish
        wait(NULL);
    }   

    // Close the file
    close(fd);
    return 0;
}
