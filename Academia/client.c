#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1" // Loopback address for testing

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send a message to the server
    const char *client_message = "Hello, server!";
    send(client_socket, client_message, strlen(client_message), 0);
    printf("Sent to server: %s\n", client_message);

    // Receive a response from the server
    ssize_t bytes_received = recv(client_socket, message, sizeof(message), 0);
    if (bytes_received > 0) {
        message[bytes_received] = '\0';
        printf("Received from server: %s\n", message);
    } else {
        perror("recv");
    }
	scanf(" %[^\n]",message);
    // Close the client socket
    close(client_socket);

    return 0;
}

