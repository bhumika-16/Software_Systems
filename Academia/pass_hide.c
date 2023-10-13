#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

// Function to read a password from the terminal without showing it
char* readPassword() {
    char* password = getpass("Enter your password: ");
    return strdup(password);
}

int main() {
    char* password = readPassword();
    
    // Now you can use the password as needed
    printf("You entered: %s\n", password);

    // Remember to free the allocated memory when done
    free(password);

    return 0;
}

