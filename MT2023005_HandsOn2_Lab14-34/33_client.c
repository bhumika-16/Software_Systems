/*
===========================================================================================
Name : 33_client.c  
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
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Port number
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    // Loopback address - Replace with the server's IP address

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send data to the server
    const char* message = "Hello, server!";
    send(client_socket, message, strlen(message), 0);
    printf("Sent to server: %s\n", message);

    // Receive a response from the server
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Received from server: %s\n", buffer);

    // Close the socket
    close(client_socket);
    return 0;
}
