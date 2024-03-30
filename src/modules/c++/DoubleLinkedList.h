#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "Node.hpp"
#include "Observe.hpp"

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;
// C++ data structure for dynamic memory usage with node linking in both directions
// Inherits Observable class behaviour to allow other segments of code to observe any changes on 
// a instance
template <typename T>
class DoubleLinkedList : public Observable {
    private:
        Node<T>* head;
        Node<T>* tail;
    public:
        int size;
        // Creates a new DoublyLinkedList with no elements
        DoubleLinkedList() : head(nullptr), tail(nullptr), size(0){
            this->current = type0;
        }
        // Inserts a new node at the end of the list
        void InsertAtEnd(T data) {
            // Normal functionality
            Node<T>* newNode = new Node<T>(data);
            if (this->tail != nullptr) {
                this->tail->next = newNode;
                newNode->prev = this->tail;
            } else {
                this->head = newNode;
            }
            this->tail = newNode;
            this->size++;
            // For observers
            this->current = type1;
            this->notifyObservers();
        }
        // Inserts a node at the front of the list
        void InsertAtFront(T data){
            // Normal behaviour
            Node<T>* newNode = new Node<T>(data);
            if (this->head != nullptr){
                this->head->prev = newNode;
                newNode->next = this.head;
            } else {
                this->tail = newNode;
            }
            this->head = newNode;
            this->size++;
            // For observers
            this.current = type1;
            this->notifyObservers();
        }
        // Gets a pointer to a node in memory from its index
        // Returns nullptr if the list has no nodes
        Node<T>* GetNode(int index){
            // Normal functionality
            if (index >= this->size || index < 0){
                throw std::out_of_range("Index out of range");
            }
            int counter = 0;
            Node<T>* current = this->head;
            while (current != nullptr){
                if (counter == index){
                    break;
                }
                current = current->next;
                counter++;
            }
            return current;
        }
        // Gets a pointer to a node in memory from its index
        Node<T>* operator[](int index){
            return GetNode(index);
        }
        // Deletes a node(element) of the list based on its data contained
        void deleteNode(T data) {
            // Normal operations
            Node<T>* current = this->head;
            while (current != nullptr) {
                if (current->data == data) {
                    Node<T>* temp = current;
                    current = current->next;
                    delete temp;

                    if (current == nullptr) {
                        tail = nullptr;
                    }
                    this->size--;
                    // For observers
                    this->current = type1;
                    this->notifyObservers();
                    // Stop loop
                    break;
                }
                current = current->next;
            }
        }
        // Looks for a value and returns its index
        // Returns -1 if the list is empty or value not found
        int Find(T value){
            int counter = -1;
            bool notFound = true;
            Node<T>* temp = this->head;
            while (temp != nullptr){
                counter++;
                if (temp->data == value){
                    return counter;
                }
                temp = temp->next;
            }
            return -1;
        }
        // Swaps two values in the list based on their positions
        // Implicitly changes it pointers forward and backwards
        void SwapByPosition(int index1, int index2){
            if ( (index1 >= this->size || index1 < 0) || (index2 >= this->size || index2 < 0)){
                throw std::out_of_range("Either index 1 or 2 are out of range");
            }
            // Normal behaviour
            // >> Retrieve the original node references
            Node<T>* node1 = this->GetNode(index1);
                std::cout << node1->data << std::endl;
            Node<T>* node2 = this->GetNode(index2);
                std::cout << node2->data << std::endl;
            // >> Create new nodes that swap the forward and backward pointers to nodes
            Node<T>* new_node1 = new Node<T>(node1->data);
                new_node1->next = node2->next;
                new_node1->prev = node2->prev;
            Node<T>* new_node2 = new Node<T>(node2->data);
                new_node2->next = node1->next;
                new_node2->prev = node1->prev;
            if ((index1 - index2) == 1 || (index2 - index1) == 1) {
                if (index1 < index2){
                    new_node2->next = new_node1;
                    new_node1->prev = new_node2;
                } else {
                    new_node1->next = new_node2;
                    new_node2->prev = new_node1;
                }
            }
            // >> Fix the list pointer to head and tail + fix pointer for adjacent nodes to the swapped relative
            if(index1 == 0){ // Node2 swapped into Node1
                new_node2->next->prev = new_node2;
                this->head = new_node2;
            } else if (index1 == this->size-1){
                new_node2->prev->next = new_node2;
                this->tail = new_node2;
            } else {
                new_node2->next->prev = new_node2;
                new_node2->prev->next = new_node2;
            }
            if (index2 == 0){ // Node1 swapped into Node2
                new_node1->next->prev = new_node1;
                this->head == new_node1;
            } else if (index2 == this->size-1){
                new_node1->prev->next = new_node1;
                this->tail = new_node1;
            } else {
                new_node1->next->prev = new_node1;
                new_node1->prev->next = new_node1;
            }
            // >> Delete the old nodes to free memory
            delete node1;
            delete node2;
            // For observers
            this->current = type1;
            this->notifyObservers();
        }
        // Swaps two values(value1 with value2)in the list
        // Implicitly changes it pointers forward and backwards
        void Swap(T value1, T value2){
            int index1 = this->Find(value1);
            int index2 = this->Find(value2);
            this->SwapByPosition(index1, index2);
        }
        Node<T>* getHead(){
            return this->head;
        }
        // Prints all the values of the list
        void PrintList() {
            Node<T>* current = this->head;
            while (current != nullptr) {
                std::cout << current->data << ' ';
                current = current->next;
            }
            std::cout << '\n';
        }
};

#endif // DLINKEDLIST_H