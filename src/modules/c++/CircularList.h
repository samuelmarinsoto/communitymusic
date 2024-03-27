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
        Node<MP3Tags>* playingNow;  // Has a two-way link to the previous song() and the next song()
                                    // Only this node is not a reference to the origin node, but a copy of the data, in case the origin list changes
        LinkedList<string> alreadyPlayed; // List of songs(uuids) that the have already been played and wont be played again(if the origin list changes), unless it is forced
        string start;  // Reference to the id of the song that was played first, and by consequence should play again when the playlist ends
    public:
        // Creates a CircularList class build upon a DoubleLinkedList
        // Parameters:
        // origin_ptr: is pointer to the memory address where the Linked List exists
        CircularList(DoubleLinkedList<MP3Tags>* origin_ptr){
            this->origin = origin_ptr;
            this->origin->AddObserver(this);
            boost::uuids::random_generator gen;
            boost::uuids::uuid uuid = gen();
            this->identifier = boost::uuids::to_string(uuid);
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
                    break;
                default:
                    break;
            }
        }
        // Gets the size of the pointed origin
        int size(){
            return this->origin->size;
        }
        // Changes the node order on the pointed origin list
        void updateOrder(){

        }
        // Gets a list of all artists in the playlist with the uuid of the song they located at
        tuple<string, string>* retrieveArtists(){

        }
        // Returns the path the next song to reproduce
        // Implies a change of context for the currently played
        const char* moveNextSong(){

        }
        // Returns the path to the previous song to reproduce
        const char* movePrevSong(){

        }
};

#endif // CIRCULAR_H