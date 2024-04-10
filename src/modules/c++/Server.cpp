// [Header(.h) file include]
#include "Server.h"

// [Other imports]
#include <iostream>

using namespace std;

// >>> Implementation blocks <<<

// Creates an instance of Server, binds the socket to specified ip and port and starts listening for clients
// Example:
// Server server(12345, "172.16.0.176");
Server::Server(int port, const char* ip) {
    // Create the socket with TCP protocol
    this->socket_server = socket(AF_INET, SOCK_STREAM, 0);

    // Create a format address; using ip and port
    sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = inet_addr(ip);

    // Binds the socket to the created address
    int binding = bind(this->socket_server, (struct sockaddr*)&address, sizeof(address));
    if (binding < 0){ // On FAIL
        std::cout << "Binding failed at " << ip << ":" << port << std::endl;
        throw runtime_error("Failed to bind the socket to requested IP and port\n > Try using another IP or Port\n > Verify firewall access to specified ports and ips");
    } // On SUCCESS
    std::cout << "Connection started. Listening at: "<< ip << ":" << port << std::endl;
    
    // Sets up other instance attributes
    this->_origin_l = nullptr;
    this->_origin_pd = nullptr;
    this->status = true;
    this->clients.insert(0);
    this->modify_event(this->clients.get(0), string("No changes"));
    thread(&Server::start_listen, this).detach();
};

// Destroy and disconnects the server and related values
Server::~Server(){
    this->status = false;
    close(this->socket_server);
};

// Starts listening for incoming clients
void Server::start_listen(){
    listen(this->socket_server, 10);
    while (this->access_shared_status()){
        int socket_client;
        std::cout<< "Waiting for client..." << std::endl;
        socket_client = accept(this->socket_server, nullptr, nullptr);
        if (socket_client > 0){
            // Append to full list
            this->clients.insert(socket_client);
            std::cout<< "Client connected succesfully" << std::endl;

            // Open a separate thread for communication
            thread(&Server::open_new_channel, this, socket_client, this->clients.size-1).detach();
        }
    }
};

// Receives a client request string(as json) and generates a response(in json) to send
// r_tp: is type of client request
// content: json object dictionary which contains possible args for interaction with server resources
// NOTE: returned value is a pointer on dynamic memory and should be freed when it is no longer required
char* Server::load_response(cmd r_tp, Dictionary content){
    Dictionary response;
    switch ( r_tp ){
        case is_Asking:
            response.add("cmd", JSON::convert_to_value<string>("send-songs"));
            response.add("status", JSON::convert_to_value<string>("OK"));
            // TODO: Full implementation of list of songs retrieval
            response.add("attach", Value(this->PARSE_resource().content));
            break;
        case is_Exiting:
            response.add("cmd", JSON::convert_to_value<string>("exiting"));
            response.add("status", JSON::convert_to_value<string>("OK"));
            break;
        case is_VotingUp:
            response.add("cmd", JSON::convert_to_value<string>("up-vote"));
            response.add("status", JSON::convert_to_value<string>("OK"));
            response.add("id", content["id"]);
            // TODO: Full implementation of modifying the specific song attribute
            this->modify_resource(content);
            break;
        case is_VotingDown:
            response.add("cmd", JSON::convert_to_value<string>("down-vote"));
            response.add("status", JSON::convert_to_value<string>("OK"));
            response.add("id", content["id"]);
            // TODO: Full implementation of modifying the specific song attribute
            this->modify_resource(content);
            break;
        case unknown:
            response.add("cmd", content["cmd"]);
            response.add("status", JSON::convert_to_value<string>("Error"));
            response.add("attach", content["attach"]);
            response.add("detail", JSON::convert_to_value<string>("bad command"));
            break;
        default:
            break;
    }
    char* result = new char[response.content.length()+1];
    strcpy(result, response.content.c_str());

    return result;
};

// Opens up a new channel for a received socket
// client_socket: socket
// who: index of client(from linkedlist)
void Server::open_new_channel(int client_socket, int who){
    // buffer is the the allocated space for incoming messages
    char buffer[5000] = { 0 };
    // msg_raw is the "unparsed" json string(client message)
    string msg_raw_content;
    while (true) {
        recv(client_socket, buffer, sizeof(buffer), 0);
        msg_raw_content = string(buffer);
        // Parse the buffer message into the json dict
        Dictionary json(msg_raw_content);
        // Save to client event for logging
        this->modify_event(who, json.content);
        // Generate response
        if (json["cmd"].as_str()=="idling" || json["cmd"].as_str()=="send-songs"){
            char* response = this->load_response(is_Asking, json);
            send(client_socket, response, strlen(response), 0);
            free(response);
        } else if (json["cmd"].as_str()=="exiting"){
            char* response = this->load_response(is_Exiting, json);
            send(client_socket, response, strlen(response), 0);
            free(response);
            // Close this channel
            this->modify_clients(action::Remove, who);
            return;

        } else if (json["cmd"].as_str()=="up-vote"){
            char* response = this->load_response(is_VotingUp, json);
            send(client_socket, response, strlen(response), 0);
            free(response);
        } else if (json["cmd"].as_str()=="down-vote"){
            char* response = this->load_response(is_VotingDown, json);
            send(client_socket, response, strlen(response), 0);
            free(response);
        } else { // For UNKNOWN commands

        }
    }
};

bool Server::access_shared_status(){
    // lock guard to unlock on return 
    lock_guard<mutex> lock(this->shared_status);
    return this->status;
};

void Server::modify_shared_status(bool arg){
    // lock
    this->shared_status.lock();
    // modify
    this->status = arg;
    // unlock
    this->shared_status.unlock();
};

string* Server::access_event(){
    // lock guard to unlock on return
    lock_guard<mutex> lock(this->shared_event);
    return this->cli_event;
};

void Server::modify_event(int who, string change){
    // lock
    this->shared_event.lock();
    // modify
    this->cli_event[0] = to_string(who);
    this->cli_event[1] = change;
    // unlock
    this->shared_event.unlock();
}

int Server::modify_clients(action fn, int index){
    // lock guard the mutex to unlock the use of the client list upon return
    lock_guard<mutex> lock(this->shared_list);
    int client = 0;
    // determine requested method
    switch (fn){
        case Get: // Retrieve any current client on session
            client = this->clients[index];
            break;
        case Remove: // remove a client that is logging out of session
            this->clients.remove(index);
            break;
        default:
            break;
    }
    return client;
}
// Set a new resource for the server to access, only one type can be set at a time
// If a type must be changed use set_attach() again. This means both resources cant exist at the same time
void Server::set_attach(rsrc_type type, DoubleLinkedList<MP3Tags>* argL, PagedArray* argC){
    this->shared_resource.lock(); // Lock the resource for changing its contents

    switch (type){
        case rsrc_type::ARR :
            this->_origin_l = nullptr;
            this->_origin_pd = argC;
            break;
        case rsrc_type::LIST:
            this->_origin_l = argL;
            this->_origin_pd = nullptr;
            break;
    }

    this->shared_resource.unlock(); // Unlock(free) the resource so other threads can access it
}

// Parse current list or array of songs from program into a JSON array, each element of the array is dictionary with the key-values of the
// song properties accordingly
// IF no resource has been set for the server, the returned array is empty
Array Server::PARSE_resource(){
    lock_guard<mutex> lock(this->shared_resource); // Lock the resource until end of process;

    Array resource;
    if (this->_origin_l == nullptr){ // Should parse the pagedarray
        for (int i = 0; i<this->_origin_pd->getSize(); i++){
            Dictionary attributes;

            MP3Tags& song = this->_origin_pd->operator[](i);
            attributes.add("id", JSON::convert_to_value<string>(string(song.uuid)) );
            attributes.add("title", JSON::convert_to_value<string>(string(song.title)) );
            attributes.add("album", JSON::convert_to_value<string>(string(song.album)) );
            attributes.add("artist", JSON::convert_to_value<string>(string(song.artist)));
            attributes.add("upvotes", JSON::convert_to_value<int>(song.upvotes) );
            attributes.add("downvotes", JSON::convert_to_value<int>(song.downvotes) );

            resource.append(Value(attributes.content));
        }
        return resource;
    } else if (this->_origin_pd == nullptr){ // Should parse the doublelinkedlist
        Node<MP3Tags>* current = this->_origin_l->getHead();

        while (current != nullptr){
            Dictionary attributes;

            MP3Tags song = current->data;
            attributes.add("id", JSON::convert_to_value<string>(string(song.uuid)));
            attributes.add("title", JSON::convert_to_value<string>(string(song.title)) );
            attributes.add("album", JSON::convert_to_value<string>(string(song.album)) );
            attributes.add("artist", JSON::convert_to_value<string>(string(song.artist))) ;
            attributes.add("upvotes", JSON::convert_to_value<int>(song.upvotes) );
            attributes.add("downvotes", JSON::convert_to_value<int>(song.downvotes) );

            resource.append(Value(attributes.content));

            current = current->next;
        }
        return resource;
    }
    return resource;
}
// Access the program resource elements and modify the specified element attributes
void Server::modify_resource(Dictionary info){
    this->shared_resource.lock(); // Lock the resource

    if (this->_origin_l != nullptr){ // Access elements from doublelinkedlist (as an observable should notify its observers)
        if (info["cmd"].as_str() == "upvote"){
            Node<MP3Tags>* node = this->_origin_l->getHead();
            while (node != nullptr){
                if (string(node->data.uuid) == info["id"].as_str()){
                    node->data.upvotes += 1;
                    break;
                }
                node = node->next;
            }
        }
        if (info["cmd"].as_str() == "downvote"){
            Node<MP3Tags>* node = this->_origin_l->getHead();
            while (node != nullptr){
                if (string(node->data.uuid) == info["id"].as_str()){
                    node->data.upvotes -= 1;
                    break;
                }
                node = node->next;
            }
        }
    } else if (this->_origin_pd != nullptr){ // Access elements from pagedarray
        if (info["cmd"].as_str() == "upvote"){
            for (int i = 0; i<this->_origin_pd->getSize(); i++){
                if (string(this->_origin_pd->operator[](i).uuid) == info["id"].as_str()){
                    this->_origin_pd->operator[](i).upvotes += 1;
                    break;
                }
            }
        }
        if (info["cmd"].as_str() == "downvote"){
            for (int i = 0; i<this->_origin_pd->getSize(); i++){
                if (string(this->_origin_pd->operator[](i).uuid) == info["id"].as_str()){
                    this->_origin_pd->operator[](i).upvotes += 1;
                    break;
                }
            }
        }
    }

    this->shared_resource.unlock(); // Free the resource once done
}