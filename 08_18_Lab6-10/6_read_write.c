//Hands on 1: Assignment No.6 - Take input from STDIN and display on STDOUT using only read/write system calls
#include <stdio.h>
#include <unistd.h>

#define BUFF_MAX 2000
int main()
{
	int nread;
	char buff[BUFF_MAX];
	printf("Enter the characters to be read from STDIN: ");
	nread=read(STDIN_FILENO,buff,sizeof(buff));//read 1000 bytes from standard input device(keyboard), store in buffer (buff)
	buff[nread]='\0';
	fflush(0);
	printf("%d bytes read...\n",nread);
	printf("Characters written to STDOUT after reading from STDIN: ");
	write(STDOUT_FILENO,buff,nread);//print 1000 bytes from the buffer on the screen
	printf("Input read and written successfully...!!\n");
	return 0;
}	
