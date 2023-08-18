//Hands on 1: Assignment No.7 - Copy file1 into file2 ($cp file1 file2)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if(argc!=3)
	{
		printf("Invalid number of arguments...!!\n");
		return 0;
	}
	int fd_read = open(argv[1],O_RDONLY);
	int fd_write = open(argv[2], O_WRONLY|O_CREAT);
	
	if(fd_read==-1 || fd_write==-1)
		printf("Read/Write not successfull...\n");
	
	while(1)
	{
		char buf;
		int char_read = read(fd_read, &buf, 1);
		if(char_read == 0)
			break;
		int char_written = write(fd_write, &buf, char_read);
	}
	printf("Contents of source file copied to destination file...\n");
	int fd_read_close = close(fd_read);
	int fd_write_close = close(fd_write);
	
	if(fd_read_close==-1 || fd_write_close==-1)
		printf("Closing of Read/Write not successfull...\n");
	return 0;
}
