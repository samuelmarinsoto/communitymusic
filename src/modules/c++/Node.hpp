#ifndef NODE_H
#define NODE_H

#include <string>

template <typename T>
class Node {
    
    public:
        T data;
        Node* next;
        Node* prev;

        Node(T dta) : data(dta), next(nullptr), prev(nullptr){};

};

#endif