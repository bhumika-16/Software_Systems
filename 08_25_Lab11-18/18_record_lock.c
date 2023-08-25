//Hands on 1: Assignment No.18 - Write a program to perform Record locking - Implement write lock and read lock
//Create 3 records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//creating the record structure
struct Record {
    int id;
    char data[50];
};

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
	printf("Invalid number of arguments...!!\n");
	return 0;
    }
    
    const char *file_name = argv[1];    
	//Open the records file and insert 3 records into the file
    int fd = open(file_name, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    
    struct Record records[3];
    //If the file is empty then create 3 default records
    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        perror("Error getting file status");
        close(fd);
        return 1;
    }

    if (file_stat.st_size == 0) 
    {        
        printf("The given file is empty... Initialised with default values...\n");
		//Creating the array of struct Record and writing to the file		
		for (int i = 0; i < 3; i++) {
		    records[i].id = i + 1;
		    sprintf(records[i].data, "This is the default data for record %d...", i + 1);
		}
		write(fd, records, sizeof(records));
	}
	
    //Implementing Read lock (Record Locking)
    int record_id;
    printf("Enter record ID to read: ");
    scanf("%d", &record_id);

    struct flock read_lock;
    read_lock.l_type = F_RDLCK;
    read_lock.l_whence = SEEK_SET;
    read_lock.l_start = (record_id - 1) * sizeof(struct Record);
    read_lock.l_len = sizeof(struct Record);

    fcntl(fd, F_SETLKW, &read_lock);

    struct Record read_record;
    lseek(fd, (record_id - 1) * sizeof(struct Record), SEEK_SET);
    read(fd, &read_record, sizeof(struct Record));

    printf("Read Lock output: \nRecord ID: %d\nData: %s\n\n", read_record.id, read_record.data);

    // Release the lock
    read_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &read_lock);

    //Implementing Write lock (Record Locking)
    printf("Enter record ID to write: ");
    scanf("%d", &record_id);

    struct flock write_lock;
    write_lock.l_type = F_WRLCK;
    write_lock.l_whence = SEEK_SET;
    write_lock.l_start = (record_id - 1) * sizeof(struct Record);
    write_lock.l_len = sizeof(struct Record);

    fcntl(fd, F_SETLKW, &write_lock);

    struct Record new_record;
    new_record.id = record_id;
    printf("Enter new data: ");
    scanf(" %[^\n]", new_record.data); //Enter string data with spaces till \n

    lseek(fd, (record_id - 1) * sizeof(struct Record), SEEK_SET);
    write(fd, &new_record, sizeof(struct Record));
    
    printf("Data written into the file where Record id is %d\n\n",record_id);

    // Release the lock
    write_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &write_lock);

    close(fd);
    
    // Reopen the file for reading and display the total tickets done
    fd = open(file_name, O_RDONLY);    
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }
    // Read the entire contents of the file into the db array
    ssize_t bytes_read = read(fd, &records, sizeof(records));
    if (bytes_read == -1) {
        perror("Error reading the file");
        close(fd);
        return 1;
    }
    printf("Contents of the file is shown below:\nRecord ID\tRecord Data\n");
    for (int i = 0; i < 3; i++) {
        printf("%d\t\t%s\n", records[i].id, records[i].data);
    }
    close(fd);
    
    return 0;
}
