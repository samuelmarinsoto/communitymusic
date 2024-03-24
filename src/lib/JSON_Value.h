#ifndef JSONVALUE_H
#define JSONVALUE_H

#include "JSON_Dict.h"
#include "JSON_Array.h"

#include <string>
#include <type_traits>

class Dictionary;
class Array;
using namespace std;
// C++ object to represent a json value
class Value {
    public:
        string content; // Holds json formatted string
        // Creates an instance of json value from a given json value string
        Value(string json_str);
        // Destroys the Value and its contents
        ~Value();
        // Interprets the given value as int
        int as_int();
        // Interprets the given value as float
        float as_float();
        // Interprets the given value as double
        double as_double();
        // Interprets the given value as string
        string as_str();
        // Interprets the given value as bool
        bool as_bool();
        // Interprets the given value as a json dictionary
        Dictionary as_dict();
        // Interprets the given value as an json array
        Array as_array();
};


#endif //JSONVALUE_H