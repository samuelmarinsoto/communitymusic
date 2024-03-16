#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 69694
#define SERVER_IP "192.168.18.10"

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    // Create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cout << "Socket creation failed\n";
        return 1;
    }

    // Set server details
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if(inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported\n";
        return 1;
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cout << "Connection failed\n";
        return 1;
    }

    std::cout << "Connected to server\n";

    // Receive data from server
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Data received from server: " << buffer << std::endl;

    close(client_socket);

    return 0;
}
