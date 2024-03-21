#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "Node.hpp"

#include <string>
#include <iostream>

using namespace std;

template <typename T>

// Data structure for linking nodes as a list
class DoubleLinkedList {

private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    void insertAtEnd(T data) {
        Node<T>* newNode = new Node<T>(data);

        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }

        tail = newNode;
    }

    void deleteNode(T data) {
        Node<T>* curr = this->head;
        while (*curr) {
            if ((*curr)->data == data) {
                Node* temp = *curr;
                *curr = (*curr)->next;
                delete temp;

                if (*curr == nullptr) {
                    tail = nullptr;
                }

                return;
            }

            curr = &(*curr)->next;
        }
    }

    void PrintList() {
        Node* curr = head;
        while (curr) {
            std::cout << curr->data << ' ';
            curr = curr->next;
        }
        std::cout << '\n';
    }
};

#endif // DLINKEDLIST_H