/*
=======================================================================
Name : 14.c
Author : Bhumika Jindal
Description : Write a program to find the type of a file.
			a. Input should be taken from command line.
			b. program should be able to identify any type of a file.
Date: 25th Aug, 2023.
=======================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1)
    {
        perror("Error while using stat");
        return 1;
    }

    if (S_ISREG(file_stat.st_mode))
        printf("Regular file: %s\n", filename);
    else if (S_ISDIR(file_stat.st_mode)) 
        printf("Directory: %s\n", filename);
    else if (S_ISCHR(file_stat.st_mode)) 
        printf("Character device: %s\n", filename);
    else if (S_ISBLK(file_stat.st_mode)) 
        printf("Block device: %s\n", filename);
    else if (S_ISFIFO(file_stat.st_mode)) 
        printf("FIFO/pipe: %s\n", filename);
    else if (S_ISLNK(file_stat.st_mode)) 
        printf("Symbolic link: %s\n", filename);
    else if (S_ISSOCK(file_stat.st_mode)) 
        printf("Socket: %s\n", filename);
    else
        printf("Unknown type: %s\n", filename);
    return 0;
}
