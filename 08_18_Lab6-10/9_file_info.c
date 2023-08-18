//Hands on 1: Assignment No.9 - Print the required information about a given file
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void print_file_info(const char *file_path) {
    struct stat file_stat;
    if (stat(file_path, &file_stat) == 0) {
        printf("File: %s\n", file_path);
        printf("a. Inode: %ld\n", (long)file_stat.st_ino);
        printf("b. Number of Hard Links: %ld\n", (long)file_stat.st_nlink);
        printf("c. UID: %d\n", file_stat.st_uid);
        printf("d. GID: %d\n", file_stat.st_gid);
        printf("e. Size: %ld bytes\n", (long)file_stat.st_size);
        printf("f. Block Size: %ld bytes\n", (long)file_stat.st_blksize);
        printf("g. Number of Blocks: %ld\n", (long)file_stat.st_blocks);
        printf("h. Time of Last Access: %s", ctime(&file_stat.st_atime));
        printf("i. Time of Last Modification: %s", ctime(&file_stat.st_mtime));
        printf("j. Time of Last Change: %s", ctime(&file_stat.st_ctime));
    } else {
        perror("Error");
    }
}

int main() {
    char file_path[256];
    printf("Enter the path to the file: ");
    fgets(file_path, sizeof(file_path), stdin);
    // Remove the newline character from the end of the input
    file_path[strlen(file_path) - 1] = '\0';
    print_file_info(file_path);
    return 0;
}

