/*
===========================================================================================
Name : 34b.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a concurrent server.
			b. use pthread_create
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <string.h>
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>  
#include <stdlib.h>     
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>

// Function to handle client connections
void func(int *fd)
{
	char buff1[100];
    memset(buff1,0, sizeof(buff1));
	read(*fd, buff1, 100);
    printf("message from client: %s\n", buff1);
    write(*fd, "Ack from server\n", 17);
    close(*fd);
}

int main()
{
    int sfd, sz, nsd;
    struct sockaddr_in server,client; 
    char buff[100];
    pthread_t threadID;
    
    // Create socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd== -1)
    {
        perror("Error while creating socket!");
        _exit(0);
    }
    printf("Server side socket successfully created!\n");

    // Configure server address   
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(5500);
    // Bind the socket and Listen for incoming connections
    bind(sfd,(struct sockaddr *)(&server),sizeof(server));
    listen(sfd,2);
    printf("Now listening for connections on a socket!\n");
    
    while(1)
    {
    	// Accept a client connection
    	sz=sizeof(client);
    	nsd=accept(sfd,(struct sockaddr*)(&client),&sz);
    	// Create a new thread to handle the client
    	if (pthread_create(&threadID, NULL, (void *)func, &nsd))
            perror("Error while creating thread");   
    }  
    // Close the server socket   
    close(sfd);
    return 0;
}
