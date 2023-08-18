//Hands on 1: Assignment No.8 - Open a file in read only mode, read line by line and display each line as it is read.
#include <stdio.h>
#include <string.h>
#define MAX_LEN 256

int main(void)
{
	//Opening the source file in read only mode
    FILE* fp;
    fp = fopen("srcFile.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

	//Read the file line by line
    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, fp))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        //Displaying each line wen it is read
        printf("%s\n", buffer);
    }
    
    //Closing the file pointer at the end
    fclose(fp);
    return 0;
}
