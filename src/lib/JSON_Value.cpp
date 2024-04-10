#include "JSON_Value.h"

Value::Value(string json_str){
    this->content = json_str;
}

Value::~Value(){
    
}

int Value::as_int(){
    if (this->content[0] != '0' && this->content[0] != '1' && this->content[0] != '2' && this->content[0] != '3' && this->content[0] != '4'
     && this->content[0] != '5' && this->content[0] != '6' && this->content[0] != '7' && this->content[0] != '8' && this->content[0] != '9'){
        return 0;
    }
    int value;
    stringstream(this->content)  >> value;
    return value;
}

float Value::as_float(){
    if (this->content[0] != '0' && this->content[0] != '1' && this->content[0] != '2' && this->content[0] != '3' && this->content[0] != '4'
     && this->content[0] != '5' && this->content[0] != '6' && this->content[0] != '7' && this->content[0] != '8' && this->content[0] != '9'){
        return 0;
    }
    float value;
    stringstream(this->content)  >> value;
    return value;
}

double Value::as_double(){
    if (this->content[0] != '0' && this->content[0] != '1' && this->content[0] != '2' && this->content[0] != '3' && this->content[0] != '4'
     && this->content[0] != '5' && this->content[0] != '6' && this->content[0] != '7' && this->content[0] != '8' && this->content[0] != '9'){

        return 0;
    }
    double value;
    stringstream(this->content)  >> value;
    return value;
}

string Value::as_str(){
    if (this->content == "null"){
        return "null";
    }
    if (this->content[0] != '"'){
        return "";
    }
    string value = "";
    for (int i = 1; i<this->content.length()-1; i++){
        value += string(1, this->content[i]);
    }
    return value;
}

bool Value::as_bool(){
    if (this->content == "true"){
        return true;
    }
    return false;
}

Dictionary Value::as_dict(){
    if (this->content[0] != '{'){
        return Dictionary();
    }
    return Dictionary(this->content);
}

Array Value::as_array(){
    if (this->content[0] != '['){
        return Array();
    }
    return Array(this->content);
}