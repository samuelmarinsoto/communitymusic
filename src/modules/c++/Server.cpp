#include "Server.hpp"

#include <iostream>
#include <cstring>

// >>> Implementation blocks <<<
Server::Server(int port_num, std::string ip_addr) : port(port_num), ip(ip_addr){ //Constructor for the class which initializes the socket
    this->ssckt = socket(AF_INET, SOCK_STREAM, 0);
    // socket creation ------^domain^--^type^------^protocol^
    // socket has stream type to listen for clients, and 0 protocol to generate one automatically

    sockaddr_in address_ip;
        address_ip.sin_family = AF_INET;
        address_ip.sin_port = htons(this->port);
        inet_pton(AF_INET, std::strcpy(new char[this->ip.length()+1], this->ip.c_str()), &address_ip.sin_addr.s_addr);
        //------^same domain^------^convert ip string to a char array[]^----------------^reference to insert the conversion^

    bind(this->ssckt, (struct sockaddr*)&address_ip, sizeof(address_ip)); // binds the socket to start a channel for listening
    std::cout << "Connection started. Listening at: "<< this->ip << ":" << this->port << std::endl;
    this->status = true;
    this->try_connect();
};

void Server::try_connect(){
    while (this->status){
        //Accept incoming client sockets
        int clientSocket;
        std::cout<< "Waiting for client..." << std::endl;

        clientSocket = accept(this->ssckt, nullptr, nullptr); // wont continue execution until a client connects
        // add connected client to list of connections
        this->client_connections.Insert(clientSocket);
        std::cout<< "Client connected succesfully" << std::endl;
        
        std::thread(&Server::init_channel, clientSocket).join();
    }
};

void Server::init_channel(int client_socket){
    char buffer[1024] = { 0 };
    //while (true) {
        recv(client_socket, buffer, sizeof(buffer), 0);
        std::cout << buffer << std::endl;
    //}
};

void Server::finish(){
    this->status = false;
    close(this->ssckt);
};