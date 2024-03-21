#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template <typename T>

class LinkedList {
    protected:
        Node<T>* head;
    public:
        LinkedList(): head(nullptr){}

        ~LinkedList(){

        }

        void push(T data){
            
        }

        void remove(int index){

        }

        void find_remove(T data){

        }

        void pop(){

        }
};

#endif // LINKEDLIST_H