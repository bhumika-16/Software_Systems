//Hands on 1: Assignment No.17 - Part 2 - open the file, implement write lock, read the ticket number, 
//increment the number and print the new ticket number then close the file.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define trains 3

struct {
		int train_num;
		int ticket_count;
	} db;
	
struct {
		int train_num;
		int ticket_count;
	} db_all[trains];

int main()
{
	int fd, input;
	fd=open("records.txt", O_RDWR);
	printf("Select train number(1,2,3): ");
	scanf("%d",&input);
	if(input<1 || input>3)
		printf("Invalid train number...!!\n");
	
	// Implement write lock
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (input-1)*sizeof(db);
    lock.l_len = sizeof(db);  
    lock.l_pid = getpid();
    
    //Reading value of ticket number
    lseek(fd, (input-1)*sizeof(db), SEEK_SET);
    read(fd, &db, sizeof(db));
    printf("Before Entering into the critical section...\n");
    fcntl(fd, F_SETLKW, &lock);
    printf("Ticket number: %d \n",db.ticket_count);
    db.ticket_count++;
    lseek(fd,-1*sizeof(db),SEEK_CUR);
    //Updating db with new ticket number
    write(fd,&db,sizeof(db));
    printf("To book ticket, please press Enter: \n");
    getchar();
    getchar();
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock);
    printf("Booked...!!\n");
    close(fd);
    
    // Reopen the file for reading and display the total tickets done
    fd = open("records.txt", O_RDONLY);    
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }
    // Read the entire contents of the file into the db array
    ssize_t bytes_read = read(fd, &db_all, sizeof(db_all));
    if (bytes_read == -1) {
        perror("Error reading the file");
        close(fd);
        return 1;
    }
    printf("Train Number\tTickets Booked\n");
    for (int i = 0; i < trains; i++) {
        printf("%d\t\t%d\n", db_all[i].train_num, db_all[i].ticket_count);
    }
    close(fd);
    return 0;
}
