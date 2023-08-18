//Hands on 1: Assignment No.10 - Open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("Invalid number of arguments...!!\n");
		return 0;
	}
	
    const char *file_path = argv[1];
    int fd = open(file_path, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write 10 bytes to the file
    const char *data1 = "1234567890";
    ssize_t bytes_written1 = write(fd, data1, 10);
    if (bytes_written1 != 10) {
        perror("Error writing data");
        close(fd);
        return 1;
    }

    // Move the file pointer by 10 bytes using lseek
    off_t seek_offset = lseek(fd, 10L, SEEK_CUR);
    if (seek_offset == -1) {
        perror("Error seeking file");
        close(fd);
        return 1;
    }

    // Write 10 bytes after moving the file pointer
    const char *data2 = "abcdefghij";
    ssize_t bytes_written2 = write(fd, data2, 10);
    if (bytes_written2 != 10) {
        perror("Error writing data");
        close(fd);
        return 1;
    }

    printf("lseek return value: %ld\n", (long)seek_offset);
    close(fd);
    printf("Program completed successfully.\n");
    return 0;
}
