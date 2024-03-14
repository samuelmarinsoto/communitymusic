#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 69694

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[1024] = "hello world";

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    // Bind socket to IP and port
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Binding failed\n";
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        std::cerr << "Listening failed\n";
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    // Accept a client connection
    socklen_t client_address_len = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    if (client_socket < 0) {
        std::cerr << "Acceptance failed\n";
        return 1;
    }

    std::cout << "Connected to client\n";

    // Send data to the client
    send(client_socket, buffer, strlen(buffer), 0);
    std::cout << "Data sent to client: " << buffer << std::endl;

    close(server_socket);
    close(client_socket);

    return 0;
}
