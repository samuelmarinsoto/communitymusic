#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.hpp"

// C++ data structure for dynamic memory usage with node linking in one direction
template <typename T>
class LinkedList {
    protected:
        Node<T>* head;
    public:
        int size;
        // Create a new linked list data structure
        LinkedList(): head(nullptr), size(0){}
        // Destroys the linked list and its nodes
        ~LinkedList(){
            Node<T>* current = this->head;
            Node<T>* temp;
            if (current != nullptr){
                while(current->next != nullptr){
                    temp = current;
                    current = current->next;
                    delete temp;
                }
            }
        }
        // Inserts a new node at the beginning of the list
        void insert(T value){
            Node<T>* node = new Node<T>(value);
            if (this->size == 0){
                this->head = node;
            } else {
                node->next = this->head;
                this->head = node;
            }
            this->size++;
        }
        // Insert a new node at the end of the list
        void append(T value){
            Node<T>* node = new Node<T>(value);
            if (this->size == 0){
                this->head = node;
            } else {
               Node<T>* current = this->head;
               while (true){
                    if (current->next == nullptr){
                        break;
                    }
                    current = current->next;
               }
               current->next = node;
            }
            this->size++;
        }
        // Removes(and frees) a node from the list at specifed index
        void remove(int index){
            Node<T>* current = this->head;
            Node<T>* prev = nullptr;
            int counter = 0;
            while (current != nullptr){
                if (counter == index){
                    break;
                }
                prev = current;
                current = current->next;
                counter++;
            }
            if (index == 0){
                this->head = current->next;
                delete current;
                this->size--;
            } else {
                prev->next = current->next;
                delete current;
                this->size --;
            }
        }
        // Find and removes(frees) a node from the list based on its contents
        void find_remove(T search_value){
            Node<T>* current = this->head;
            if (current->data == search_value){
                Node<T>* temp = current->next;
                this->head = temp;
                delete current;
                this->size--;
            } else {
                while (current->next != nullptr){
                    if (current->next->data == search_value){
                        break;
                    }
                    current = current->next;
                }
                Node<T>* temp = current->next;
                current->next = temp->next;
                delete temp;
                this->size--;
            }
        }
        // Removes(frees) the last node of the list
        // NOTE: this node is most commonly the first one inserted
        void pop(){
            if (this->size == 1){
                delete this->head;
                this->head = nullptr;
                this->size--;
            } else if (this->size > 1){
                Node<T>* current = this->head;
                for (int i = 0; i<this->size-1 ; i++){
                    current = current->next;
                }
                Node<T>* temp = current->next;
                delete temp;
                current->next = nullptr;
                this->size--;
            }
        }
        // Get a node at a specified index
        // Returns a nullptr if the list is empty
        Node<T>* getNode(int index){
            if (index < 0){
                return nullptr;
            }
            Node<T>* node = this->head;
            int counter = 0;
            while (node!=nullptr){
                if (counter == index){
                    break;
                }
                node = node->next;
                counter++;
            }
            return node;
        }
        // Get the data of a node based on its index
        T& get(int index){
            Node<T>* node = this->head;
            for (int i = 0; i<index; i++){
                node = node->next;
            }
            return node->data;
        }
        // Get the data of a node based on its index
        T& operator[](int index){
            return this->get(index);
        }
};

#endif // LINKEDLIST_H