#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "Observe.hpp"
#include "DoubleLinkedList.h"
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
        void stopObserving(){
            this->origin->RemoveObserver(this);
        }
};

template <>
class CircularList<MP3Tags> : public Observer{
    private:
        DoubleLinkedList<MP3Tags>* origin;
        string identifier;
        LinkedList<string> alreadyPlayed; // List of songs(uuids) that the have already been played and wont be played again(if the origin list changes), unless it is forced
        string start;  // Reference to the id of the song that was played first, and by consequence should play again when the playlist ends

        // Changes the node order on the pointed origin list
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
                    if (ref->next != nullptr){
                        this->playingNow->next = new Node<MP3Tags>(ref->next->data);
                        this->playingNow->next->prev = this->playingNow;
                    }
                }
                this->start = string(this->playingNow->data.uuid);
            } else { // Once started
                this->setFollowing();
            }
        }
        // Sets a the node with better voting difference as the following node
        void setFollowing(){
            // Get the head node and iterate over the nodes to find the one with a better voting difference
            // Set the better one AS the following node
            Node<MP3Tags>* ref = this->origin->getHead();
            Node<MP3Tags>* selected = nullptr;
            int best_difference = 0;
            while(ref != nullptr){
                if ( (ref->data.upvotes - ref->data.downvotes) >= best_difference && ref != this->playingNow && this->check_played(string(ref->data.uuid)) ){
                    selected = ref;
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
            while (ref != nullptr){
                if(string(ref->data.uuid) == this->alreadyPlayed.get(this->alreadyPlayed.size -1)){
                    this->alreadyPlayed.pop();
                    this->playingNow->prev = new Node<MP3Tags>(ref->data);
                    this->playingNow->prev->next = this->playingNow;
                }
                ref = ref->next;
            }
        }
        // Checks if a song has already been played or not
        // Compares their unique uuids
        // Returns FALSE if not found, TRUE if found
        bool check_played(string uuid){
            Node<MP3Tags>* ref = this->origin->getHead();
            while (ref != nullptr){
                if (string(ref->data.uuid) == uuid){
                    return true;
                }
                ref = ref->next;
            }
            return false;
        }
    public:
        Node<MP3Tags>* playingNow;  // Has a two-way link to the previous song() and the next song()
                                    // Only this node is not a reference to the origin node, but a copy of the data, in case the origin list changes
        bool conditioned;

        // Creates a CircularList class build upon a DoubleLinkedList
        // Parameters:
        // origin_ptr: is pointer to the memory address where the Linked List exists
        CircularList(DoubleLinkedList<MP3Tags>* origin_ptr){
            this->origin = origin_ptr;
            this->origin->AddObserver(this);
            boost::uuids::random_generator gen;
            boost::uuids::uuid uuid = gen();
            this->identifier = boost::uuids::to_string(uuid);
            this->conditioned = false;
            this->playingNow = nullptr;
            this->start = "";
        }
        // Destroys the circular list
        ~CircularList(){
            delete playingNow->next;
                playingNow->next = nullptr;
            delete playingNow->prev;
                playingNow->prev = nullptr;
            delete playingNow;
        }
        // CircularList implementation of Observer update method upon changes of observable
        void update(State state) override {
            switch (state){
                case type1:
                    std::cout << "Observer " << this->identifier <<" => " <<"List contents were modified" << std::endl;
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
        // Returns and pointer to the list, and hence the pointer should be deallocated when it will be no longer used
        string* retrieveArtists(){
            return nullptr;
        }
        // Moves to the next song(pointer)
        // Implies a change of context for the currently played
        // If <reached_end> is set to true then the moved song is added to the already played list of songs
        void moveNextSong(){
            delete this->playingNow->prev;
                this->playingNow->prev = nullptr;

            this->alreadyPlayed.insert(string(this->playingNow->data.uuid));

            if (this->origin->size == this->alreadyPlayed.size){ // What happens when the playlist has reached its end
                // Reset all the played song ids
                while (this->alreadyPlayed.size > 0){
                    this->alreadyPlayed.pop();
                }
                // Set back the start of the list at the first node
                this->conditioned = false;
                this->updateOrder();
                this->setFollowing();
                this->conditioned = true;
            }else {
                this->playingNow = this->playingNow->next;
                this->setFollowing();
            }
        }
        // Moves back to the previous song(pointer)
        // Implies a change of context for the currently played
        // If <reached_end> is set to true then the moved song is added to the already played list of songs
        void movePrevSong(){
            if (this->playingNow->prev == nullptr){
                // Throw exception
            }
            delete this->playingNow->next;
                this->playingNow->next = nullptr;

            this->playingNow = this->playingNow->prev;
            this->setPrevious();
        }
};

#endif // CIRCULAR_H