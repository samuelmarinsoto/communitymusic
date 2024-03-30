#include "JSON_Array.h"

Array::Array(){
    this->content = "[]";
}

Array::Array(string json_string){
    this->content = json_string;
    // Read values saved in the string of the array
        // >> value-related: saving values in 'this->values'
    string n_value = "";
        // >> parsing json
    int case_count = 0;
    for (int i=0; i<json_string.length(); i++){
        switch (json_string[i]){
            case ']':
                if (case_count == 1){
                    case_count --;
                    n_value += string(1, json_string[i]);
                } else if (case_count == 0){
                    if (n_value != ""){
                        this->values.push_back(n_value);
                        n_value = "";
                    }
                } else if (case_count > 1){
                    case_count--;
                    n_value += string(1, json_string[i]);
                }
                break;

            case '}':
                if (case_count>0){
                    case_count--;
                }
                n_value += string(1, json_string[i]);
                if (case_count == 0){
                    this->values.push_back(n_value);
                    n_value = "";
                }
                break;
            
            case ',':
                if (case_count>0){
                    n_value += string(1, json_string[i]);
                }else if (case_count==0){
                    this->values.push_back(n_value);
                    n_value = "";
                }
                break;

            default:
                if ((json_string[i]=='{' || (json_string[i]=='[') && i>0)) {
                    case_count++;
                    n_value += string(1, json_string[i]);
                } else if (i>0) {
                    n_value += string(1, json_string[i]);
                }
                break;
        }
    }
}

Value Array::operator[](int index){
    if (this->values.size() == 0){
        return Value("");
    }
    return Value(this->values[index]);
}

void Array::append(Value value){
    this->values.push_back(value.content);
}

void Array::pop(){
    this->values.pop_back();
}

void Array::remove(int index){
    string new_content = "[";
    // ^^^^ fill this string with current pairs(saved on the vector)
    //          and avoid the specified key
    vector < string > new_values;
    // ^^NOTE^^: in the same loop the vector with the pairs will be reconstructed
    for (int i=0; i<this->values.size(); i++) {
        string current = this->values[i];
        if (i != index){
            if (i>0){
                new_content += ",";
            }
            new_values.push_back(current);
            new_content = new_content + current;
        }
    }
    new_content += "]";
    // change the respective attributes
    this->content = new_content;
    this->values = new_values;
}

int Array::size(){
    return this->values.size();
}

Array::~Array(){
    
}