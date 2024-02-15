#ifndef NODE_H
#define NODE_H

#include <string>

template <typename T>
class Node {
    public:
    //----------------[Class atributes]----------------//
        T data;
        Node* next;
        Node* prev;
    //----------------[Class atributes]----------------//

        Node(T dta) {
        data = dta;
        next = nullptr;
        prev = nullptr;
    }

};

#endif