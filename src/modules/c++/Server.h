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
#include <glog/logging.h>

using namespace std;
class Server{
    // ----------------------------------------- ATTRIBUTES
    private:
        // Holds the socket of the server
        int socket_server;
        // Loads all clients into this list
        LinkedList<int> clients;
        mutex shared_list;

        //Current status of the server(ON or OFF)
        bool status;
        mutex shared_status;

        string cli_event[2];
        mutex shared_event;
    protected:
        mutex shared_resource;
        DoubleLinkedList<MP3Tags>* _origin_l;
        PagedArray* _origin_pd;
    // ----------------------------------------- METHODS
    public:
        Server(int port, const char* ip);
        ~Server();

        bool access_shared_status();
        void modify_shared_status(bool arg);
        string* access_event();
        void set_attach(rsrc_type type, DoubleLinkedList<MP3Tags>* argL, PagedArray* argC);
    private:
        void start_listen();
        char* load_response(cmd r_tp, Dictionary content);
        void open_new_channel(int client, int who);
        // Parse the current resource into a JSON object to share via sockets
        Array PARSE_resource();
    protected:
        int modify_clients(action fn, int index);
        void modify_event(int who, string change);
        // Modify values of the reference resources from an accepted client action
        void modify_resource(Dictionary info);
};

#endif // SERVER_H
