#ifndef NODE_H
#define NODE_H

#include <string>

// Generic dynamic memory object to contain any given data
// Required in linear data structures
template <typename T>
class Node {
    public:
        T data;
        Node* next;
        Node* prev;
        // Builds a node saving the given data inside
        Node(T dta) : data(dta), next(nullptr), prev(nullptr){};
        // Destroy a node
        ~Node(){}
};

#endif // NODE_H