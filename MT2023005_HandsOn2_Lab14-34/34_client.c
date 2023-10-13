/*
===========================================================================================
Name : 34_client.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a concurrent server.
			a. use fork
			b. use pthread_create
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>     
#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

int main()
{
    int sfd, cstatus;
    struct sockaddr_in address;     
    char buff[100];
    
    // Create socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd== -1)
    {
        perror("Error while creating socket!");
        _exit(0);
    }
    printf("Client side socket successfully created...!!\n");

	// Configure server address
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_family = AF_INET;
    address.sin_port = htons(5500);
    
    // Connect to the server
    cstatus=connect(sfd, (struct sockaddr *)&address, sizeof(address));
    if (cstatus == -1)
    {
        perror("Error while connecting to server!\n");
        _exit(0);
    }
    printf("Client to server connection successfully established!!\n");

	//Communication with the server
    printf("Sending data from client to the server...\n");
    write(sfd, "Hello from the client\n", 23);
    read(sfd, buff, 100);
   	printf("Data received from server: %s\n", buff);
   	
    printf("------------Press any key to terminate connection----------");
    getchar();
    printf("\nProgram Exiting...\n");
    // Close the client socket
    close(sfd);
    return 0;
}
