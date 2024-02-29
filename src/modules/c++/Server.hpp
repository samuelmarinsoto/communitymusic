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

using namespace std;

class Server{
    private:
        int port;
        string ip;
        int s_socket;
        LinkedList<int> client_connections;
        bool status;
    
    protected:
        void listen_for();
        string load_response(string input);
        void open_new_channel(int client_socket);

    public:
        Server(int port_num, string ip_addr);
        ~Server();

};

#endif