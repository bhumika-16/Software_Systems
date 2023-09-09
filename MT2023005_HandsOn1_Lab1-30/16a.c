/*
=======================================================================
Name : 16a.c
Author : Bhumika Jindal
Description : Write a program to perform mandatory locking.
			a. Implement write lock
Date: 25th Aug, 2023.
=======================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() 
{
    const char *file_name = "lock_file.txt";
    int fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    const char *message = "This is a sample text.\n";
    write(fd, message, strlen(message));

    // Implement write lock
    struct flock write_lock;
    write_lock.l_type = F_WRLCK;
    write_lock.l_whence = SEEK_SET;
    write_lock.l_start = 0;
    write_lock.l_len = 0;  // Lock the entire file
    write_lock.l_pid = getpid();
    
    if (fcntl(fd, F_SETLKW, &write_lock) == -1) {
        perror("Error acquiring write lock");
        close(fd);
        return 1;
    }
	printf("Inside the Critical Section of write lock...\n");
    printf("Write lock acquired. Press Enter to release the lock...\n");
    getchar();
	printf("Unlocked!\n");
    // Release the write lock
    write_lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &write_lock) == -1) {
        perror("Error releasing write lock");
        close(fd);
        return 1;
    }
    printf("Write lock released.\n\n");
    close(fd);
    return 0;
}
