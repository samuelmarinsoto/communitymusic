#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "Observe.hpp"
#include "DoubleLinkedList.hpp"
#include "LinkedList.hpp"
#include "MP3Tags.hpp"
#include "Node.hpp"

#include <iostream>
#include <string>
#include <tuple>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
// Specialized C++ data structure of a bidirectional circular linked list
// Works as a reference to existent linked list and implements an Observer pattern to get all its changes
// Functionality is similar to a priority queue, as it arranges elements based on a evaluated value
template <typename T>
class CircularList : public Observer{
    private:
        DoubleLinkedList<T>* origin;
        string identifier;
    public:
        // Creates a CircularList class build upon a DoubleLinkedList
        // Parameters:
        // origin_ptr: is pointer to the memory address where the Linked List exists
        CircularList(DoubleLinkedList<T>* origin_ptr){
            this->origin = origin_ptr;
            this->origin->AddObserver(this);
            boost::uuids::random_generator gen;
            boost::uuids::uuid uuid = gen();
            this->identifier = boost::uuids::to_string(uuid);
        }
        ~CircularList(){}
        // CircularList implementation of Observer update method upon changes of observable
        void update(State state) override {
            switch (state){
                case type1:
                    std::cout << "Observer[" << this->identifier <<"] => " <<"List contents were modified" << std::endl;
                    break;
                default:
                    break;
            }
        }
        // Gets the size of the pointed origin
        int size(){
            return this->origin->size;
        }
        // Removes this observer class from the observable
        void stopObserving() override {
            this->origin->RemoveObserver(this);
        }
};

template <>
class CircularList<MP3Tags> : public Observer{
    // ------------------------------------- ATTRIBUTES
    protected:
        DoubleLinkedList<MP3Tags>* origin;
    private:
        LinkedList<string> alreadyPlayed; // List of songs(uuids) that the have already been played and wont be played again(if the origin list changes), unless it is forced
    public:
        Node<MP3Tags>* playingNow;  // Has a two-way link to the previous song() and the next song()
                                    // Only this node is not a reference to the origin node, but a copy of the data, in case the origin list changes
        bool conditioned;

    // ------------------------------------- ATTRIBUTES
    protected:
        // Changes the node order based on the pointed origin list
        void updateOrder(){
            if (!this->conditioned){ // When the mp3 reproduction hasn't started
                Node<MP3Tags>* ref = this->origin->GetNode(0); // A reference to the first node of the DoubleLinkedList
                // Before changing any values must deallocate the pointers from memory
                if (this->playingNow != nullptr){
                    delete this->playingNow->next;
                    delete this->playingNow->prev;
                }
                delete this->playingNow;
                this->playingNow = nullptr;
                // Now its viable to change any data
                if (ref != nullptr){
                    this->playingNow = new Node<MP3Tags>(ref->data); // Create a copy node of the contents
                }
            }
            this->setFollowing();
        }
    private:
        // Sets a the node with better voting difference as the following node
        void setFollowing(){
            // Get the head node and iterate over the nodes to find the one with a better voting difference
            // Set the better one AS the following node
            Node<MP3Tags>* ref = this->origin->getHead();
            Node<MP3Tags>* selected = nullptr;
            int best_difference = 0;
            bool initial_state = true;
            while(ref != nullptr){
                if (initial_state && ( (ref->data.upvotes - ref->data.downvotes) >= best_difference || (ref->data.upvotes - ref->data.downvotes) < best_difference )
                && string(ref->data.uuid) != string(this->playingNow->data.uuid) && !this->check_played(string(ref->data.uuid))){
                    selected = ref;
                    best_difference = selected->data.upvotes - selected->data.downvotes;
                    initial_state = false;
                }
                if (!initial_state && (ref->data.upvotes - ref->data.downvotes) >= best_difference && string(ref->data.uuid) != string(this->playingNow->data.uuid) && !this->check_played(string(ref->data.uuid)) ){
                    selected = ref;
                    best_difference = selected->data.upvotes - selected->data.downvotes;
                }
                ref = ref->next;
            }
            if (selected != nullptr){
                delete this->playingNow->next;
                this->playingNow->next = nullptr;
                
                this->playingNow->next = new Node<MP3Tags>(selected->data);
                this->playingNow->next->prev = this->playingNow;
            }
        }
        // Sets a node marked as previously played as the
        void setPrevious(){
            Node<MP3Tags>* ref = this->origin->getHead();
            Node<string>* last_id = this->alreadyPlayed.getNode(0);
            
            while (ref != nullptr && last_id!=nullptr){ 
                if( string(ref->data.uuid) == last_id->data ) {
                    this->alreadyPlayed.remove(0);
                    this->playingNow->prev = new Node<MP3Tags>(ref->data);
                    this->playingNow->prev->next = this->playingNow;
                    break;
                }
                ref = ref->next;
            }
        }
        // Checks if a song has already been played or not
        // Compares their unique uuids
        // Returns FALSE if not found, TRUE if found
        bool check_played(string uuid){
            Node<string>* ref = this->alreadyPlayed.getNode(0);
            while (ref != nullptr){
                if (ref->data == uuid){
                    return true;
                }
                ref = ref->next;
            }
            return false;
        }
    public:
        // Creates a CircularList class build upon a DoubleLinkedList
        // Parameters:
        // origin_ptr: is pointer to the memory address where the Linked List exists
        CircularList(DoubleLinkedList<MP3Tags>* origin_ptr){
            // Observer elements
            this->origin = origin_ptr;
            this->origin->AddObserver(this);
            // Class elements
            this->conditioned = false;
            this->playingNow = nullptr;
        }
        // Destroys the circular list
        ~CircularList(){
            if (playingNow != nullptr){
                if (playingNow->next != nullptr){
                    delete playingNow->next;
                        playingNow->next = nullptr;
                }
                if (playingNow->prev != nullptr){
                    delete playingNow->prev;
                        playingNow->prev = nullptr;
                }
                delete playingNow;
            }
        }
        // CircularList implementation of Observer update method upon changes of observable
        void update(State state) override {
            switch (state){
                case type1:
                    std::cout << "(CircularList)Observer" << " ! => " <<"List contents were modified" << std::endl;
                    this->updateOrder();
                    break;
                case type2:
                    std::cout << "(CircularList)Observer" << " ! => " <<"List contents were modified" << std::endl;
                    this->updateOrder();
                    break;
                default:
                    break;
            }
        }
        // Gets the size of the pointed origin
        int size(){
            return this->origin->size;
        }
        // Forcefully modifies the current song for play and changes its pointers
        // Only usable for user decision
        // Expects a valid UUID represented as a string
        void ForceSetCurrent(string song_id){
            delete this->playingNow->next;
                this->playingNow->next = nullptr;
            delete this->playingNow->prev;
                this->playingNow->prev = nullptr;
            Node<MP3Tags>* current = this->origin->getHead();
            while (current != nullptr){
                if (string(current->data.uuid) == song_id){
                    break;
                }
                current = current->next;
            }
            Node<MP3Tags>* new_node = new Node<MP3Tags>(current->data);
                this->playingNow->next = new_node;
                new_node->prev = this->playingNow;
            
            this->playingNow = new_node;

            this->setFollowing();
        }
        // Gets an array of all artists in the playlist with their songs in the current playlist
        void getPlaylistArtists(string artists[], size_t size){
            Node<MP3Tags>* current = this->origin->getHead();
            int counter = 0;
            while (current != nullptr){
                string current_artist = string(current->data.artist);
                bool repeated = false;
                for (int i = 0; i<size; i++){
                    if (artists[i] == current_artist){
                        repeated = true;
                        break;
                    }
                }
                if (!repeated){
                    artists[counter++] = current_artist;
                }
                current = current->next;
            }
        }
        // Gets all the current playlist songs of an specific artist
        vector<string> getArtistSongs(string artist_name){
            vector<string> found_songs;
            Node<MP3Tags>* current = this->origin->getHead();

            while (current != nullptr){
                if (string(current->data.artist) == artist_name){
                    found_songs.push_back(string(current->data.title));
                }
                current = current->next;
            }

            return found_songs;
        }
        // Moves to the next song(pointer)
        // Implies a change of context for the currently played
        void moveNextSong(){
            delete this->playingNow->prev;
                this->playingNow->prev = nullptr;

            this->alreadyPlayed.insert(string(this->playingNow->data.uuid));

            if (this->origin->size == this->alreadyPlayed.size){ // What happens when the playlist has reached its end
                // Reset all the played song ids
                while (this->alreadyPlayed.size > 1){
                    this->alreadyPlayed.remove(0);
                }
                // Delete current nodes
                delete this->playingNow->next;
                delete this->playingNow->prev;
                delete this->playingNow;
                this->playingNow = nullptr;
                // Set back the start of the list at the first node
                Node<MP3Tags>* node = this->origin->getHead();
                string start_id = this->alreadyPlayed.getNode(0)->data;
                while (node != nullptr){
                    if ( string(node->data.uuid) == start_id){
                        break;
                    }
                    node = node->next;
                }
                this->playingNow = new Node<MP3Tags>(node->data);
                this->setFollowing();
                this->alreadyPlayed.remove(0);
            } else {
                this->playingNow = this->playingNow->next;
                this->setFollowing();
            }
        }
        // Moves back to the previous song(pointer)
        // Implies a change of context for the currently played
        void movePrevSong(){
            if (this->playingNow->prev != nullptr){
                delete this->playingNow->next;
                    this->playingNow->next = nullptr;

                this->playingNow = this->playingNow->prev;
                this->alreadyPlayed.remove(0);
                this->setPrevious();
            }
        }
        // Removes this observer class from the observable
        void stopObserving() override {
            this->origin->RemoveObserver(this);
            this->origin = nullptr;
        }
};

#endif // CIRCULAR_H