#include "record_struct.h"
#define PORT 8080
#define SERVER_IP "127.0.0.2" // Loopback address for testing

void client_handle(int socket);
int main() 
{
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
    // Successfully connected to the server
	printf("Client to server connection successfully established...\n");
	
	//Communication with the server
	client_handle(client_socket);
	
    // Close the client socket
    close(client_socket);
    return 0;
}

void client_handle(int socket)
{
	char buff[1024]; 
    struct message m;
    ssize_t readBytes, writeBytes;            
    char temp_buff[1024];

    do{
       	memset(buff, 0,sizeof(buff));   
        memset(m.buff, 0,sizeof(m.buff));
        readBytes = read(socket,&m, sizeof(m));
        if (readBytes == -1)
            perror("Error while reading from client socket!!\n");
        else if (readBytes == 0)
            printf("No msg from Portal... Please reload this program\n");        
        else
        {
        	printf("%s",m.buff);
         	if(m.response==1)
         	{
         		//scanf(" %[^\n]", buff); 
         		memset(buff, 0,sizeof(buff));       		
        		fgets(buff, sizeof(buff), stdin);
        		fflush(stdin);
        		if (strlen(buff) > 0 && buff[strlen(buff) - 1] == '\n')
            		buff[strlen(buff) - 1] = '\0';
        		writeBytes = write(socket,buff,strlen(buff)); 
    		}
    	}
     }while (readBytes > 0);
    close(socket);
}
