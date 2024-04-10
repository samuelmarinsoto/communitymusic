#ifndef fJSON_H
#define fJSON_H

#include "JSON_Array.h"
#include "JSON_Dict.h"
#include "JSON_Value.h"

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>


class Array;
class Dictionary;
class Value;

using namespace std; // simplies writing "std:: . . . "
// Library for json file and parsing
namespace JSON{
    // Reads a json file from a path and convert it into single-lined raw string
    // ready for parsing
    string read(const string filePath);
    // Removes all the insignificant decimal values(all zeros) and rounds up
    // Keeps the number with precision
    string remove_decimals(string number);
    // Parse a string with json format into a dictionary
    Dictionary parse(string json_string);

    // Converts a given data type into a json value
    template <typename T>
    Value convert_to_value(T data);
};


#endif //fJSON_H