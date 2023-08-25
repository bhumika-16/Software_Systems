//Hands on 1: Assignment No.17 - Part 1 - Program to open a file, store a ticket number and exit.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define trains 3
#define initial 100

int main()
{
	//Insert train number and tickets booked in the database
	int i,fd;
	struct {
		int train_num;
		int ticket_count;
	} db[trains];
	
	//Initialising the array of struct with initial values
	for(i=0;i<trains;i++)
	{
		db[i].train_num=i+1;
		db[i].ticket_count=initial;
	}
	
	//Open the file and write the struct records
	fd = open("records.txt", O_RDWR|O_CREAT, 0777);
	if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }
	//int wr = write(fd, &db, sizeof(struct trains_struct)*trains);
	if( write(fd, &db, sizeof(db)) == -1)
		perror("Cannot write the file...\n");
	close(fd);
	
	// Reopen the file for reading
    fd = open("records.txt", O_RDONLY);    
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }

    // Read the entire contents of the file into the db array
    ssize_t bytes_read = read(fd, &db, sizeof(db));
    if (bytes_read == -1) {
        perror("Error reading the file");
        close(fd);
        return 1;
    }
    // Print the updated information
    printf("Train Number\tTickets Booked\n");
    for (i = 0; i < trains; i++) {
        printf("%d\t\t%d\n", db[i].train_num, db[i].ticket_count);
    }
    close(fd);
    
	return 0;
}
