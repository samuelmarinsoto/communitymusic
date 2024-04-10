#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

// Dynamically allocated array for variable size arrays
template <typename T>
class vect {
    private:
        T* arr;
        int reserved_size;
    public:
        int size; // Current KNOWN size of the vector.

        // Creates a new vector object with no elements
        // Needs to know its initial size, all elements for the initial vector will be set to default value
        vect(){
            this->arr = new T[5];
            this->size = 0;
            this->reserved_size = 5;
        };
        // Destroys and wipes the vector from memory
        ~vect(){
            delete[] this->arr;
        };
        // Retrieves data at the specified index
        T operator[](int index){
            if (index < this->size){
                return this->arr[index];
            } else {
                throw std::out_of_range("Index out of range");
            }
        };
        // Allows assigning new values to indexed elements
        void set(int index, T value){
            if (index>=this->size){
                throw std::out_of_range("Value index out of range");
            }
            this->arr[index] = value;
        }
        // Removes(pops) the last element in the vector
        void pop(){
            if (this->size > 0){
                this->size--;
            }
        };
        // Inserts a new element at the front of the vector
        // Implies moving each element one position forward
        void push(T value){
            if (this->size == this->reserved_size){
                // Modify the array size and allocate a new array
                this->reserved_size += 5;
                T* new_arr = new T[this->reserved_size];
                // Pass all elements of the arr to the new one
                new_arr[0] = value;
                for (int i = 1; i <= this->size; i++){
                    new_arr[i] = this->arr[i-1];
                }
                delete[] this->arr;
                // Change the pointer to the new place in memory
                this->arr = new_arr;
                // Increase size by 1
                this->size++;
            } else if (this->size < this->reserved_size){
                if (this->size > 1){
                    // Move the elements of the list
                    T insertion, temp;
                    insertion = value;
                    for (int i = 0; i < this->size; i++){
                        temp = this->arr[i];
                        this->arr[i] = insertion;
                        insertion = temp; 
                    }
                } else if (this->size == 0){
                    this->arr[0] = value;
                } else if (this->size == 1){
                    this->arr[1] = this->arr[0];
                    this->arr[0] = value;
                }
                // Increase size
                this->size++;

            }
        };
        // Inserts an element at the end of the list
        void append(T value){
            if (this->size == this->reserved_size){
                // Modify the array size and allocate a new array
                this->reserved_size += 5;
                T* new_arr = new T[this->reserved_size];
                // Pass all elements of the arr to the new one
                for (int i = 0; i < this->size; i++){
                    new_arr[i] = this->arr[i];
                }
                delete[] this->arr;
                // Change the pointer to the new place in memory
                this->arr = new_arr;
                // Add new element and increase size by 1
                this->arr[this->size] = value;
                this->size++;
            } else if (this->size < this->reserved_size){
                // Add new element and increase size by 1
                this->arr[this->size] = value;
                this->size++;
            }
        };

};

#endif // VECTOR_H