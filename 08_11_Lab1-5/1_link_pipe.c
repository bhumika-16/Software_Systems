//Hands on 1: Assignment No. - 1(a) and 1(b) and 1(c) Using System Calls

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
