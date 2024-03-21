#ifndef NODE_H
#define NODE_H

#include <string>

template <typename T>

// Generic dynamic memory object to contain any given object
class Node {

    public:
        T data;
        Node* next;
        Node* prev;

        // Builds a node saving the given data inside
        Node(T dta) : data(dta), next(nullptr), prev(nullptr){};

};

#endif // NODE_H