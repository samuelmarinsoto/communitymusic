#ifndef NODE_H
#define NODE_H

#include <string>
#include "SongData.hpp"

template <typename T>
class Node {
    public:
    //----------------[Class atributes]----------------//
        T data;
        Node* next;
        Node* prev;
    
    //-------------------[Class constructor]-------------------//
        Node(T dta) {
        data = dta;
        next = nullptr;
        prev = nullptr;
    }

};

template<>
class Node<SongData> {
    public:
    //------------------[Class atributes]------------------//
        SongData content;
        Node<SongData>* next;
        Node<SongData>* prev;

    //-------------------[Class methods]-------------------//
    Node(std::string path): content(path){
        next = nullptr;
        prev = nullptr;
    }
};

#endif