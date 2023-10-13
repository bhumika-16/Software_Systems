/*
===========================================================================================
Name : 34a.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to create a concurrent server.
			a. use fork
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
#include <sys/stat.h>

int main()
{
    int sfd, sz, nsd;
    struct sockaddr_in server,client; 
    char buff[100];

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
    // Bind the socket
    bind(sfd,(void *)(&server),sizeof(server));
    // Listen for incoming connections
    listen(sfd,5);
    printf("Now listening for connections on a socket!\n");
    
    while(1)
    {
    	// Accept a client connection
		sz=sizeof(client);
		nsd=accept(sfd,(void*)(&client),&sz); 
		
		// Fork a new process to handle the client
   		if(fork()==0)
   		{
   		 	// This is the child process, handle the client
   		 	close(sfd);
	    	memset(buff,0, sizeof(buff));
	   		read(nsd, buff, 100);
       		printf("Message Received from client: %s\n", buff);
       		write(nsd, "Ack from server\n", 17);
       		close(nsd);
            exit(0); // Terminate the child process
    	}
        else
        	close(nsd); // Close the client socket in the parent
    }
    // Close the server socket (This part will not be reached in practice)
    close(sfd);
    return 0;
}
