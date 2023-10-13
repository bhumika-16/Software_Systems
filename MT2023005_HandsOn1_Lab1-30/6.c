/*
===============================================================================
Name : 6.c
Author : Bhumika Jindal
Description : Write a program to take input from STDIN and display on STDOUT. 
			Use only read/write system calls
Date: 18th Aug, 2023.
===============================================================================
*/

#include <stdio.h>
#include <unistd.h>

#define BUFF_MAX 2000
int main()
{
	int nread;
	char buff[BUFF_MAX];
	printf("Enter the characters to be read from STDIN: ");
	//read 2000 bytes from standard input device(keyboard), store in buffer (buff)
	nread=read(STDIN_FILENO,buff,sizeof(buff));
	buff[nread]='\0';
	fflush(0);
	printf("%d bytes read...\n",nread);
	printf("Characters written to STDOUT after reading from STDIN: ");
	//print 2000 bytes from the buffer on the screen
	write(STDOUT_FILENO,buff,nread);
	printf("Input read and written successfully...!!\n");
	return 0;
}	
