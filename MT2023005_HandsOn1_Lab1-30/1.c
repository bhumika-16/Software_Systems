/*
==============================================================================================
Name : 1.c
Author : Bhumika Jindal
Description : Create the following types of a files using (i) shell command (ii) system call
				a. soft link (symlink system call)
				b. hard link (link system call)
				c. FIFO (mkfifo Library Function or mknod system call)
Date: 11th Aug, 2023.
==============================================================================================
*/

/*For doing this using terminal:
$ln dest destHL
$ln -s dest destSL
$ls -l
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	//Create dest file using: touch dest. 
	//Link Names files must not exists in the folder.
	int v = symlink("dest","destSL");
	if(v<0)
		{perror("Failed"); return 1;}
		
	int f=link("dest","destHL");
	if(f<0)
		{perror("Failed"); return 1;}
		
	int e=mknod("destFIFO",S_IFIFO,0);
	if(e<0)
		perror("Failed");
	return 0;
}	
