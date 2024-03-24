#ifndef JSONDICT_H
#define JSONDICT_H

#include "JSON_Array.h"
#include "JSON_Value.h"
#include "Vector.hpp"

#include <string>
#include <tuple>

class Array;
class Value;
using namespace std;
// C++ object for a json dictionary
// Use this to parse any json file represented as a string
class Dictionary {
    private:
        vect< tuple<string, string> > pairs;
        bool verify_existence(string key);
        void rebuild();
    public:
        string content; // Current dictionary in its json format
        // Creates a dictionary from a given string using json format
        Dictionary(string json_string);
        // Creates a new empty dictionary
        Dictionary();
        // Destroys the dictionary and its contents
        ~Dictionary();
        // Looks for a json value based on the received key
        Value operator[](string key);
        // Adds a new key-value pair
        // IF they given key already exists, then its value will be overwritten
        void add(string key, Value value);
        // Removes the key-pair value from the dictionary based on the key
        void remove(string key);
};

#endif //JSONDICT_H