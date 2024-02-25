#ifndef SERVER_H
#define SERVER_H

#include "LinkedList.hpp"

#include <cstring>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <thread>

class Server{
    private:
        int port;
        std::string ip;
        int s_socket;
        LinkedList<int> client_connections;
        bool status;
    
    protected:
        void listen_for();
        //int COM_with(char* msg, int *socket_recipient);
        void open_new_channel(int client_socket);

    public:
        Server(int port_num, std::string ip_addr);

        void finish();

};

#endif