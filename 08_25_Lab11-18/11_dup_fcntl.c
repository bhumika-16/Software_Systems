//Hands on 1: Assignment No.11 - Open a file, duplicate the file descriptor and append the file with both the descriptors 
//and check whether the file is updated properly or not using dup, dup2 and fcntl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
	printf("Invalid number of arguments...!!\n");
	return 0;
    }
    // Open the file
    const char *file_name = argv[1];    
    int fd = open(file_name, O_RDWR | O_CREAT);

    // Method 1: Using dup
    int fd_dup = dup(fd);
    const char *m1 = "Using dup...Hello! How are you?\n";
    write(fd_dup, m1, strlen(m1));
    close(fd_dup);

    // Method 2: Using dup2
    int fd_dup2 = dup2(fd, fd+1);
    const char *m2 = "Using dup2...Hey..I am fine!!\n";
    write(fd_dup2, m2, strlen(m2));
    close(fd_dup2);

    // Method 3: Using fcntl
    int fd_fcntl = fcntl(fd, F_DUPFD);
    const char *m3 = "Using fcntl...Thank You...!!\n";
    write(fd_fcntl, m3, strlen(m3));
    close(fd_fcntl);

    // Close the original file descriptor
    close(fd);
    // Check whether the file is updated properly
    char buffer[1024];
    FILE *file = fopen(file_name, "r");
    if (file) {
        printf("File content:\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL)
            printf("%s", buffer);
        fclose(file);
    } else {
        perror("Error opening the file");
        return 1;
    }
    return 0;
}

