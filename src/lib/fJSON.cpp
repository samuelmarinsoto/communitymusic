#include "fJSON.hpp"

string JSON::read(const string filePath){
        std::ifstream file(filePath);
        std::stringstream buffer;
        buffer << file.rdbuf();
        
        std::string true_str = buffer.str();
            true_str.erase(std::remove_if(true_str.begin(), true_str.end(), ::isspace), true_str.end());
            //^^ removes all whitespaces, newlines and tabs
        return true_str;
}

string JSON::remove_decimals(string number){
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
}

Dictionary JSON::parse(string json_string){
    return Dictionary(json_string);
};

template <typename T>
Value JSON::convert_to_value(T data){
    return Value("");
}

template <>
Value JSON::convert_to_value(bool data){
    // Boolean case
    if (data){
        return Value("true");
    } else {
        return Value("false");
    }
}

template <>
Value JSON::convert_to_value(int data){
    // Integer case
    string number = std::to_string(data);
    return Value(number);
}

template <>
Value JSON::convert_to_value(double data){
    // Double case
    string number = std::to_string(data);
    number = JSON::remove_decimals(number);
    return Value(number);
}

template <>
Value JSON::convert_to_value(float data){
    // Float case
    string number = std::to_string(data);
    number = JSON::remove_decimals(number);
    return Value(number);
}

template <>
Value JSON::convert_to_value(string data){
    // String case
    string str = "\"";
    str += data;
    str += "\"";
    return Value(str);
}

template <>
Value JSON::convert_to_value(Dictionary data){
    // json dictionary case
    string copy = data.content;
    return Value(copy);
}

template <>
Value JSON::convert_to_value(Array data){
    // json array case
    string copy = data.content;
    return Value(copy);
}