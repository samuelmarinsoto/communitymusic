#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "JSON_Dict.h"
#include "JSON_Value.h"
#include "Vector.hpp"

#include <string>
#include <tuple>


class Dictionary;
class Value;
using namespace std;
// C++ object for a json array of values
class Array {
    private:
        vect<string> values;
    public:
        string content; // Current array in json format
        // Creates a json array from given string using json formatting
        Array(string json_string);
        // Creates a new empty json array
        Array();
        // Destroys array
        ~Array();
        // Looks for a json value in the array based on its index
        Value operator[](int index);
        // Appends a new value at the end of the array
        void append(Value value);
        // Removes last element of the array
        void pop();
        // Removes element at specified index
        void remove(int index);
        // Returns the size of the json array
        int size();
};

#endif //JSONARRAY_H