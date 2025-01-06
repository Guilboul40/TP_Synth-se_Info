#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> 

#define USAGE_MSG "Usage: %s <host> <file>\n"
#define ADDRESS_OBTAINED_MSG "Address obtained for host.\n"
#define SOCKET_CREATED_MSG "Socket created successfully.\n"
#define SOCKET_ERROR_MSG "Error creating socket.\n"
// Function to handle command-line arguments
void handle_arguments(int argc, char *argv[], const char **host, const char **filename) {
    if (argc != 3) {
        fprintf(stderr, USAGE_MSG, argv[0]);
        exit(1); // Exit on error
    }
    *host = argv[1]; // Retrieve the host
    *filename = argv[2]; // Retrieve the filename
}
// Function to obtain the address of a host
struct addrinfo* get_address_info(const char *host, const char *port) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints)); // Initialize the hints structure
    hints.ai_family = AF_INET; // Use IPv4
    hints.ai_socktype = SOCK_DGRAM; // Use UDP

    int status = getaddrinfo(host, port, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return NULL; // Return NULL on error
    }
    printf(ADDRESS_OBTAINED_MSG);

    // Print the resolved address
    char ipstr[INET_ADDRSTRLEN]; // Buffer for the IP address
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr; // Cast to IPv4
    inet_ntop(AF_INET, &ipv4->sin_addr, ipstr, sizeof(ipstr)); // Convert to string
    printf("Resolved IP address: %s\n", ipstr); // Print the IP address

    return res; // Return the address
}
// Function to create a socket
int create_socket(struct addrinfo *res) {
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        perror("socket");
        return -1; // Return -1 on error
    }
    return sockfd; // Return the socket descriptor
}
// Main function
int main(int argc, char *argv[]) {
    const char *host;
    const char *filename;

    // Step 1: Handle command-line arguments
    handle_arguments(argc, argv, &host, &filename);
    printf("Host: %s, File: %s\n", host, filename);
    
    // Step 2: Obtain the address
    struct addrinfo *res = get_address_info(host, "1069"); // Specify the port
    if (!res) {
        return 1; // Exit on error
    }
    // Step 3: Create the socket
    int sockfd = create_socket(res);
    if (sockfd < 0) {
        freeaddrinfo(res); 
        fprintf(stderr, SOCKET_ERROR_MSG);
        return 1; // Exit on error
    }

    printf(SOCKET_CREATED_MSG);
    // Cleanup
    freeaddrinfo(res);
    close(sockfd); // Close the socket
    return 0; // Successful exit
}
