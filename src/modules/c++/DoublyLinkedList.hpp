#ifndef DoublyLinkedList_H
#define DoublyLinkedList_H

//Files imports
    #include "Node.hpp"
    #include "SongData.hpp"
//Modules imports
    #include <string>
    #include <iostream>

template <typename T>
class DoublyLinkedList{
    protected:
    //-----------------[Class attributes]-----------------//
        int size;
    public:
    //-----------------[Class method]-----------------//
        int getSize() const {
            return this->size;
        }
};

template <>
class DoublyLinkedList<int> : public DoublyLinkedList<void> {
    private:
    //-----------------[Class attributes]-----------------//
        Node<int> *head;
    public:
    //-----------------[Class constructor]-----------------//
        DoublyLinkedList() {
            this->head = nullptr;
            this->size = 0;
        }
    //-----------------[Class methods]-----------------//
        void Insert(int insertion_value) { // Insert an integer into a new node of the list
            Node<int>* node = new Node<int>(insertion_value);
            if (this->size = 0){
                node->next = this->head;
            }else{
                this->head->prev = node;
                node->next = this->head;node->next = this->head;
            }

            this->head = node;
            this->size++;
        }

        Node<int>* Get_Head() const{
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

        Node<int>* Get_reverse(int index) const{
            return nullptr;
        }

        int Get_indexOf(int search_value){ // Searches for the first instance of node that contains the search value; returns -1 if it doesnt exist
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

        int Get_indexOf_reverse(int search_value){ // Searches for the first intance of node that contains the search value; returns -1 if it doesnt exist
            return 0;
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

    template <>
    class DoublyLinkedList<SongData> : DoublyLinkedList<void>{
            private:
            //-----------------[Class attributes]-----------------//
                Node<SongData> *head;
            public:
            //-----------------[Class constructor]-----------------//
                DoublyLinkedList() {
                    this->head = nullptr;
                    this->size = 0;
                }
            //-----------------[Class methods]-----------------//
                void Insert(std::string song_path) { // Insert an integer into a new node of the list
                    Node<SongData>* node = new Node<SongData>(song_path);
                    if (this->size = 0){
                        node->next = this->head;
                    }else{
                        this->head->prev = node;
                        node->next = this->head;node->next = this->head;
                    }

                    this->head = node;
                    this->size++;
                }

                Node<SongData>* Get_Head() const{
                    return this->head;
                }

                Node<SongData>* Get(int index) const{ // Retrieves a node(element) of the list at the specified index
                    int counter = 0;
                    Node<SongData>* current = this->head;
                    while (index>0 && counter<index){
                        current = current->next;
                        counter++;
                    }
                    return current;
                };
    };

#endif