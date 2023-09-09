//Hands on 1: Assignment No.16 - Program to perform mandatory locking - Implement write lock and read lock
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
    
    // Implement read lock
    struct flock read_lock;
    read_lock.l_type = F_RDLCK;
    read_lock.l_whence = SEEK_SET;
    read_lock.l_start = 0;
    read_lock.l_len = 0;  // Lock the entire file
    read_lock.l_pid = getpid();
    
    if (fcntl(fd, F_SETLKW, &read_lock) == -1) {
        perror("Error acquiring read lock");
        close(fd);
        return 1;
    }
	printf("Inside the Critical Section of read lock...\n");
    printf("Read lock acquired. Press Enter to release the lock...\n");
    getchar();
	printf("Unlocked!\n");
    // Release the read lock
    read_lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &read_lock) == -1) {
        perror("Error releasing read lock");
        close(fd);
        return 1;
    }
    printf("Read lock released.\n");

    close(fd);
    return 0;
}
