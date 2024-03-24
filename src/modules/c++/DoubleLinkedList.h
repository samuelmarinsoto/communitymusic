#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "Node.hpp"

#include <string>
#include <iostream>

using namespace std;
// C++ data structure for dynamic memory usage with node linking in both directions
template <typename T>
class DoubleLinkedList {

private:
    Node<T>* head;
    Node<T>* tail;
public:
    int size;
    // Creates a new DoublyLinkedList with no elements
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    // Inserts a new node at the end of the list
    void insertAtEnd(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }

        tail = newNode;
        this->size++;
    }
    // Deletes a node(element) of the list based on its data contained
    void deleteNode(T data) {
        Node<T>* current = this->head;
        while (current != nullptr) {
            if ((*current)->data == data) {
                Node<T>* temp = current;
                current = current->next;
                delete temp;

                if (current == nullptr) {
                    tail = nullptr;
                }
                this->size--;
                return;
            }

            current = current->next;
        }
    }
    // Prints all the values of the list
    void PrintList() {
        Node<T>* current = this->head;
        while (current) {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }
};

#endif // DLINKEDLIST_H