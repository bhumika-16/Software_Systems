#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 5

// Function to handle client connections
void *handle_client(void *arg) 
{
    int client_socket = *((int *)arg);
    char buffer[1024];
    ssize_t bytes_received;

    // Receive data from the client
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("Received from client: %s\n", buffer);

        // Send an acknowledgment back to the client
        const char *acknowledgment = "Message received by the server.";
        send(client_socket, acknowledgment, strlen(acknowledgment), 0);
    }

    // Client disconnected or encountered an error
    if (bytes_received == 0) {
        printf("Client disconnected: %d\n", client_socket);
    } else {
        perror("recv");
    }

    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t threads[MAX_CLIENTS];

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a client connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Accepting connection failed");
            continue; // Continue listening for other connections
        }

        // Create a new thread to handle the client
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, &client_socket);
        pthread_detach(tid); // Detach the thread to clean up automatically
    }

    // Close the server socket (This part will not be reached in practice)
    close(server_socket);

    return 0;
}

