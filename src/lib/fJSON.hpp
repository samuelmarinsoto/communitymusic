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
// Removes all the insignificant decimal values(all zeros) and rounds up
// Keeps the number with precision
string remove_decimals(string number){
    bool point = false;
    int decimal_count = 0;
    int non_decimal_count = 0;
    int zeros = 0;
    for (int i = 0; i<number.length(); i++){
        // Non-decimal places
        if (number[i] == '.'){
            point = true;
        }
        if (number[i] != '.' && !point){
            non_decimal_count++;
        }
        // Decimal places
        if (number[i] != '0' && point){
            if (zeros == 0){
                decimal_count++;
            } else if (zeros>0){
                decimal_count = decimal_count+zeros+1;
                zeros = 0;
            }
        }
        if (number[i] == '0' && point){
            zeros++;
        }
    }
    // Suppose an integer
    if (decimal_count == 0){
        return number;
    }
    // Modify into new float or double
    int string_range = non_decimal_count+decimal_count;
    string new_number = "";
    for (int j = 0; j<string_range; j++){
        new_number += string(1, number[j]);
    }
    return new_number;
};
// Library for json file and parsing
namespace JSON{
    // Reads a json file from a path and convert it into single-lined raw string
    // ready for parsing
    string read(const string filePath){
        std::ifstream file(filePath);
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        std::string true_str = buffer.str();
            true_str.erase(std::remove_if(true_str.begin(), true_str.end(), ::isspace), true_str.end());
            //^^ removes all whitespaces, newlines and tabs
        return true_str;
    };
    // Parse a string with json format into a dictionary
    Dictionary parse(string json_string){
        return Dictionary(json_string);
    };

    // Converts a given data type into a json value
    template <typename T>
    Value convert_to_value(T data){
        return Value("");
    };

    template <>
    Value convert_to_value<bool> (bool data){
        // Boolean case
        if (data){
            return Value("true");
        } else {
            return Value("false");
        }
    }

    template <>
    Value convert_to_value<int> (int data){
        // Integer case
        string number = std::to_string(data);
        number = remove_decimals(number);
        return Value(number);
    }

    template <>
    Value convert_to_value<double> (double data){
        // Double case
        string number = std::to_string(data);
        number = remove_decimals(number);
        return Value(number);
    }

    template <>
    Value convert_to_value<float> (float data){
        // Float case
        string number = std::to_string(data);
        number = remove_decimals(number);
        return Value(number);
    }

    template <>
    Value convert_to_value<string> (string data){
        // String case
        string str = "\"";
        str += data;
        str += "\"";
        return Value(str);
    }

    template <>
    Value convert_to_value<Dictionary> (Dictionary data){
        // json dictionary case
        string copy = data.content;
        return Value(copy);
    }

    template <>
    Value convert_to_value<Array> (Array data){
        // json array case
        string copy = data.content;
        return Value(copy);
    }
};


#endif //fJSON_H