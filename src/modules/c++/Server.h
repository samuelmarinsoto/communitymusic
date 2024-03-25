#ifndef SERVER_H
#define SERVER_H

// >>> Module imports <<<
#include "args.h"
#include "lib/fJSON.hpp"
#include "LinkedList.hpp"

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
        /* Attach files
        ListaDoble* canciones;
        ArregloPaginado* canciones;
        */

    protected:
        void start_listen();
        char* load_response(cmd r_tp, Dictionary content);
        void open_new_channel(int client, int who);

        int modify_clients(action fn, int index);

        // void set_ref_attach(Rsrc which, Lista* argL, Paginada* argC);
        // void modify_ref_attach();
    public:
        Server(int port, const char* ip);
        ~Server();

        bool accces_shared_status();
        void modify_shared_status(bool arg);

        string* access_event();
        void modify_event(int who, string change);
};

#endif // SERVER_H