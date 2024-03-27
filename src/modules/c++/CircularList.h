#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "Observe.hpp"
#include "DoubleLinkedList.h"
#include "MP3Tags.hpp"

// Specialized C++ data structure of a bidirectional circular linked list
// Works as a reference to existent linked list and implements an Observer pattern to get all its changes
// Functionality is similar to a priority queue, as it arranges elements based on a evaluated value
template <typename T>
class CircularList : public Observer{
    private:
        DoubleLinkedList<T>* origin;
    public:
        // Creates a CircularList class build upon a DoubleLinkedList
        // Parameters:
        // origin_ptr: is pointer to the memory address where the Linked List exists
        CircularList(DoubleLinkedList<T>* origin_ptr){
            this->origin = origin_ptr;
            this->origin->AddObserver(this);
        }
        ~CircularList(){}
        // CircularList implementation of Observer update method upon changes of observable
        void update(State state) override {

        }
        // Gets the size of the pointed origin
        int size(){
            return this->origin->size;
        }
        // Changes the node order on the pointed origin list
        void organizeNodes(){

        }
};

template <>
class CircularList<MP3Tags> : public Observer{
    private:
        DoubleLinkedList<MP3Tags>* origin;
    public:
        // Creates a CircularList class build upon a DoubleLinkedList
        // Parameters:
        // origin_ptr: is pointer to the memory address where the Linked List exists
        CircularList(DoubleLinkedList<MP3Tags>* origin_ptr){
            this->origin = origin_ptr;
            this->origin->AddObserver(this);
        }
        ~CircularList(){}
        // CircularList implementation of Observer update method upon changes of observable
        void update(State state) override {

        }
        // Gets the size of the pointed origin
        int size(){
            return this->origin->size;
        }
        // Changes the node order on the pointed origin list
        void organizeNodes(){

        }
};

#endif // CIRCULAR_H