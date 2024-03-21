#ifndef LinkedList_H
#define LinkedList_H

//Files imports
    #include "Node.hpp"
//Modules imports
    #include <string>
    #include <iostream>

//Generic Father class
    class Generic {
        protected:
            int size; // Class atribute for the linked list size
        public:
            int get_size() const{ //Common method for all classes
                return this->size;
            }
    };
//--------------------------||--------------------------//
    template <typename T>

    class LinkedList : Generic{};

    template <> // Data type: INTEGER
    class LinkedList<int> : public Generic{
        private:
            Node<int>* head;
        public:

            LinkedList() : head(nullptr) {
                this->size = 0;
            }

            void Insert(int x) { // Inserts an integer into the list
                Node<int>* node = new Node<int>(x);
                node->next = this->head;

                this->head = node;
                this->size++;
            };

            Node<int> *Get_head() const { // Retrieves the head of the list via ptr
                return this->head;
            }

            Node<int>* Get(int index) const{ // Retrieves a node(element) of the list at the specified index
                int counter = 0;
                Node<int>* current = this->head;
                while (index>0 && counter<index){
                    current = current->next;
                    counter++;
                }
                return current;
            };

            int Get_indexOf(int search_value){ // Searches for the first intance of node that contains the search value; returns -1 if it doesnt exist
                Node<int>* current = this->head;
                int counter = 0;
                while (current->next != nullptr){
                    if(current->data == search_value){
                        return counter;
                    }
                    current = current->next;
                    counter++;
                }
                return -1;
            }

            void Remove(int index) { // Removes a node(element) at a specified index
                int counter = 0;
                Node<int>* current = this->head;
                if (index>0){
                    while (counter < index-1) { // Finds the previous node to the one to be removed
                        current = current->next;
                        counter++;
                    }
                    Node<int>* to_remove = current->next;
                    //Update pointer and isolate node-to-remove
                    current->next = to_remove->next;
                    to_remove->next = nullptr;
                    //Delete node-to-remove from memory heap
                    delete to_remove;
                } else if (index == 0){
                    this->head = current->next;
                    current->next = nullptr;
                    delete current;
                }

                this->size--;
            }
    };

    template <> // Data type: DOUBLE
    class LinkedList<double> : public Generic {
        private:
            Node<double>* head;
        public:

            LinkedList() : head(nullptr) {
                this->size = 0;
            }

            void Insert(double x) { // Inserts an integer into the list
                Node<double>* node = new Node<double>(x);
                node->next = this->head;

                this->head = node;
                this->size++;
            };

            Node<double> *Get_head() const { // Retrieves the head of the list via ptr
                return this->head;
            }

            Node<double>* Get(int index) const{ // Retrieves a node(element) of the list at the specified index
                int counter = 0;
                Node<double>* current = this->head;
                while (index>0 && counter<index){
                    current = current->next;
                    counter++;
                }
                return current;
            };

            int Get_indexOf(int search_value){ // Searches for the first intance of node that contains the search value; returns -1 if it doesnt exist
                Node<double>* current = this->head;
                int counter = 0;
                while (current->next != nullptr){
                    if(current->data == search_value){
                        return counter;
                    }
                    current = current->next;
                    counter++;
                }
                return -1;
            }

            void Remove(int index) { // Removes a node(element) at a specified index
                int counter = 0;
                Node<double>* current = this->head;
                if (index>0){
                    while (counter < index-1) { // Finds the previous node to the one to be removed
                        current = current->next;
                        counter++;
                    }
                    Node<double>* to_remove = current->next;
                    //Update pointer and isolate node-to-remove
                    current->next = to_remove->next;
                    to_remove->next = nullptr;
                    //Delete node-to-remove from memory heap
                    delete to_remove;
                } else if (index == 0){
                    this->head = current->next;
                    current->next = nullptr;
                    delete current;
                }

                this->size--;
            }
    };

    template <> // Data type: STRING
    class LinkedList<std::string> {
        private:
            Node<std::string>* head;
            int size;
        public:
            LinkedList() : head(nullptr), size(0) {}
    };
//--------------------------||--------------------------//

#endif // LinkedList_H