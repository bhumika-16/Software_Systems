#include "Admin.h"
#define PORT 8080
#define MAX_CLIENTS 5

// Function to handle client connections
void *handle_conn(void *arg) 
{
	printf("Client has connected to the server...!\n");
	int client_socket = *((int *)arg);
    char buff[1024];
    struct message m;
    ssize_t readBytes, writeBytes;
    int ch;

   	while(1)
   	{
    	memset(m.buff,0,sizeof(m.buff));
       	strcpy(m.buff,"------------------------------ Welcome to Academia : Course Registration Portal ----------------------------\n\
Login Type (1.Admin  2.Professor  3.Student) \nPlease enter your login choice: ");
       	m.response=1;
       	write(client_socket, &m, sizeof(m));
       	
   	   	memset(buff,0,sizeof(buff));
        readBytes = read(client_socket, buff, sizeof(buff));        
        if (readBytes == -1)
            perror("Error while reading from client!!\n");
        else if (readBytes == 0)
            printf("Client disconnected: No data was sent by the client...\n");        
        else
        {   
            ch = atoi(buff);
            switch (ch)
            {
            case 1:
            	memset(m.buff,0,sizeof(m.buff));
                strcpy(m.buff,"Hello Administrator! Press Enter to continue...\n" );
        		m.response=1;
        		write(client_socket, &m, sizeof(m));
        		admin_operation_handler(client_socket);
                break;
            case 2:
            	memset(m.buff,0,sizeof(m.buff));
                strcpy(m.buff,"Hello Professor! Press Enter to continue...\n" );
        		m.response=1;
        		write(client_socket, &m, sizeof(m));
                break;
            case 3:
            	memset(m.buff,0,sizeof(m.buff));
                strcpy(m.buff,"Hello Student...\n" );
        		m.response=1;
        		write(client_socket, &m, sizeof(m));
                break;
            default:
                // Exit
                memset(m.buff,0,sizeof(m.buff));
                strcpy(m.buff,"Invalid choice...\nReopening the application with Login Page...\n" );
        		m.response=0;
        		write(client_socket, &m, sizeof(m));
                break;
            }
        }
    }
    printf("Terminating connection to client!\n");
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
        pthread_create(&tid, NULL, handle_conn, &client_socket);
        pthread_detach(tid); // Detach the thread to clean up automatically
    }

    // Close the server socket (This part will not be reached in practice)
    close(server_socket);
    return 0;
}
