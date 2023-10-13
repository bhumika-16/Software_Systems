/*
===========================================================================================
Name : 33_server.c  
Author : Bhumika Jindal
Roll No. : MT2023005
Description : Write a program to communicate between two machines using socket.
Date: 22nd Sept, 2023.
===========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[1024];

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080); // Port number

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    // Accept a client connection
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }

    // Receive data from the client
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);

    // Send a response to the client
    const char* response = "Hello, client!";
    send(client_socket, response, strlen(response), 0);
	printf("Sent to client: %s\n", response);
	
    // Close sockets
    close(client_socket);
    close(server_socket);
    return 0;
}
