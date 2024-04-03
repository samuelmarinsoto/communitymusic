#ifndef SERVER_H
#define SERVER_H

// >>> Module imports <<<
#include "args.h"
#include "../../lib/fJSON.hpp"
#include "LinkedList.hpp"
#include "DoubleLinkedList.hpp"
#include "PagedArray.hpp"
#include "MP3Tags.hpp"

// >>> Main imports <<< 
#include <cstring>
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <mutex>
#include <stdexcept>

class Server{
    private:
        // Holds the socket of the server
        int socket_server;
        // Loads all clients into this list
        LinkedList<int> clients;
        
        // The shared mutex allows modifying the following values: status and cli_event
        mutex shared_status;
        mutex shared_event;
        mutex shared_list;

        //Current status of the server(ON or OFF)
        bool status;
        //String value
        string cli_event[2];
        // App resources
        DoubleLinkedList<MP3Tags>* _origin_l;
        PagedArray* _origin_pd;
    protected:
        void start_listen();
        char* load_response(cmd r_tp, Dictionary content);
        void open_new_channel(int client, int who);

        int modify_clients(action fn, int index);
        
        // Set a new resource for the server to access, only one type can be set at a time
        // If a type must be changed use set_attach() again. This means both resources cant exist at the same time
        void set_attach(rsrc_type type, DoubleLinkedList<MP3Tags>* argL, PagedArray* argC);
        Dictionary PARSE_resource();
        void modify_resource(Dictionary client_action);
    public:
        Server(int port, const char* ip);
        ~Server();

        bool accces_shared_status();
        void modify_shared_status(bool arg);

        string* access_event();
        void modify_event(int who, string change);
};

#endif // SERVER_H