#include "Server.hpp"

#include <iostream>
#include <cstring>

// >>> Implementation blocks <<<
Server::Server(int port_num, std::string ip_addr) : port(port_num), ip(ip_addr){ //Constructor for the class which initializes the socket
    this->s_socket = socket(AF_INET, SOCK_STREAM, 0);
    // socket creation ------^domain^--^type^------^protocol^
    // socket has stream type to listen for clients, and 0 protocol to generate one automatically

    sockaddr_in address_ip;
        address_ip.sin_family = AF_INET;
        address_ip.sin_port = htons(this->port);
        inet_pton(AF_INET, std::strcpy(new char[this->ip.length()+1], this->ip.c_str()), &address_ip.sin_addr.s_addr);
        //------^same domain^------^convert ip string to a char array[]^----------------^reference to insert the conversion^

    bind(this->s_socket, (struct sockaddr*)&address_ip, sizeof(address_ip)); // binds the socket to start a channel for listening
    std::cout << "Connection started. Listening at: "<< this->ip << ":" << this->port << std::endl;
    this->status = true;
    this->listen_for();
};

void Server::listen_for(){
    listen(this->s_socket, 10);
    while (this->status){
        //Accept incoming client sockets
        int clientSocket;
        std::cout<< "Waiting for client..." << std::endl;
        clientSocket = accept(this->s_socket, nullptr, nullptr); // wont continue execution until a client connects
        if (clientSocket > 0){
            // add connected client to list of connections
            this->client_connections.Insert(clientSocket);
            std::cout<< "Client connected succesfully" << std::endl;
            
            std::thread(&Server::open_new_channel, this, clientSocket).join();
        }
        sleep(10);
    }
};

void Server::open_new_channel(int client_socket){
    char buffer[1024] = { 0 };
    //while (true) {
        recv(client_socket, buffer, sizeof(buffer), 0);
        std::cout << buffer << std::endl;
    //}
};

void Server::finish(){
    this->status = false;
    close(this->s_socket);
};