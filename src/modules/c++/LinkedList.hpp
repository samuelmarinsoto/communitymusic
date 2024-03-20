#ifndef LinkedList_H
#define LinkedList_H

#include "Node.hpp"
#include <string>
#include <iostream>

using namespace std;

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void insertAtEnd(T data) {
        Node* newNode = new Node{data, nullptr};

        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }

        tail = newNode;
    }

    void deleteNode(T data) {
        Node** curr = &head;
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

#endif // LinkedList_H
