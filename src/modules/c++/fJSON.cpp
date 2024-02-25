// Header include
#include "fJSON.hpp"

#include <iostream>
// >>> Implementation blocks <<<

std::string json_as_string(const std::string filePath){ // Access a JSON file and serialize it to string
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    std::string true_str = buffer.str();
        true_str.erase(std::remove_if(true_str.begin(), true_str.end(), ::isspace), true_str.end());
        //^^ removes all whitespaces, newlines and tabs
    return true_str;
};

// JSONObject methods
JSONObject::JSONObject() : inserting_point(0){
    this->content = "{}";
};

JSONObject::JSONObject(string jsonString){
    this->content = jsonString;
    this->inserting_point = this->content.length()-2;
    // Retrieve key-value pairs from the given string
        //tuple-related
    tuple<string, string> n_pair = make_tuple("","");
        //parsing json
    string reading = "";
    bool hasSeenKey = false;
    int subcase = 0;
    for ( int i=0 ; i<jsonString.length() ; i++) {
        // key detection --> when " : " is spotted
        if (!hasSeenKey && jsonString[i]==':'){
            hasSeenKey = true;
            get<0> (n_pair) = reading;
            reading = "";
            i++;
        }
        // value construction --> based on char case
        if (hasSeenKey){
            switch (jsonString[i]){
                case '}':
                    // complete the value and save to tuple
                    if (subcase == 1){
                        subcase--;
                        reading += string(1, jsonString[i]);
                        get<1> (n_pair) = reading;
                        reading = "";
                        this->pairs.push_back(n_pair);
                        n_pair = make_tuple("","");
                        hasSeenKey = false;
                    } else if (subcase == 0){
                        if (reading!="") {
                            get<1> (n_pair) = reading;
                            reading = "";
                            this->pairs.push_back(n_pair);
                            n_pair = make_tuple("","");
                            hasSeenKey = false;
                        }
                    } else if (subcase > 1){
                        subcase--;
                        reading += string(1, jsonString[i]);
                    }
                    break;

                case ',':
                    // complete the value and save to tuple
                    if (subcase>0){
                        reading += string(1, jsonString[i]);
                    }else if (subcase == 0){
                        get<1> (n_pair) = reading;
                        reading = "";
                        this->pairs.push_back(n_pair);
                        n_pair = make_tuple("","");
                        hasSeenKey = false;
                    }
                    break;
                
                case ']':
                    if (subcase>0){
                        subcase--;
                    }
                    reading += string(1, jsonString[i]);
                    if (subcase == 0){
                        get<1> (n_pair) = reading;
                        reading = "";
                        this->pairs.push_back(n_pair);
                        n_pair = make_tuple("","");;
                        hasSeenKey = false;
                    }
                    break;

                default:
                    if (jsonString[i]=='['){
                        subcase++;
                    } else if (jsonString[i]=='{'){
                        subcase++;
                    }
                    reading += string(1, jsonString[i]);
                    break;
            }
        }
        // key construction -> ignores most symbols except ":"
        if (!hasSeenKey && (jsonString[i]!='{' && jsonString[i]!='}' && jsonString[i]!='[' && jsonString[i]!=']' &&  jsonString[i]!=',' && jsonString[i]!='"')){
            reading += string(1,jsonString[i]);
        }
    }
};

string JSONObject::Get(string key){

}

int JSONObject::getInt(string key){
    for (int i = 0; i<this->pairs.size(); i++){
        if (get<0> (this->pairs[i]) == key){
            int value;
            stringstream(get<1> (this->pairs[i])) >> value;
            return value;
        }
    }
    return -1;
}

float JSONObject::getFloat(string key){
    for (int i=0; i<this->pairs.size(); i++){
        if (get<0> (this->pairs[i]) == key){
            float value;
            stringstream(get<1> (this->pairs[i])) >> value;
            return value;
        }
    }
    return -0,07;
}

string JSONObject::getString(string key){
    for (int i=0; i<this->pairs.size(); i++){
        if (get<0> (this->pairs[i]) == key){
            string value = get<1> (this->pairs[i]);
            if (value[0]=='"' && value[value.length()-1]=='"'){
                string retrn = "";
                for (int j=1; j<value.length()-1; j++){
                    retrn += string(1, value[j]);
                }
                return retrn;
            } else {
                return "!!!";
            }
        }
    }
    return "!!!";
}

bool JSONObject::getBool(string key){
    for (int i=0; i<this->pairs.size(); i++){
       if (get<0> (this->pairs[i]) == key){
            if (get<1> (this->pairs[i]) == "false"){
                return false;
            } else if (get<1> (this->pairs[i]) == "true"){
                return true;
            }
        } 
    }
    return false;
}

JSONObject JSONObject::getObject(string key){
 for (int i=0; i<this->pairs.size(); i++){
    if (get<0> (this->pairs[i])==key){
        return JSONObject(get<1> (this->pairs[i]));
    }
 }
 return JSONObject();
}

JSONArray JSONObject::getArray(string key){
 for (int i=0; i<this->pairs.size(); i++){
    if (get<0> (this->pairs[i])==key){
        return JSONArray(get<1> (this->pairs[i]));
    }
 }
 return JSONArray();
}

bool JSONObject::isNull(string key){
    return false;
}

void JSONObject::append(string key, int value){
    // cast value to string
    string str_value = to_string(value);
    // remove the last element: '}'
    this->content.pop_back();
    // create string pair to-insert
    string new_pair = "";
    if (this->inserting_point>0){
        new_pair += ",";
    }
    new_pair = new_pair + string(1, '"') + key + string(1, '"') + ":" + str_value + "}";
    // replace content on instance & add to vector
    this->content += new_pair;
    tuple<string, string> pair = make_tuple(key, str_value);
    this->pairs.push_back(pair);
    this->inserting_point = this->content.length()-2;
}

void JSONObject::append(string key, float value){
    // cast value to string
    string str_value = to_string(value);
    // remove the last element: '}'
    this->content.pop_back();
    // create string pair to-insert
    string new_pair = "";
    if (this->inserting_point>0){
        new_pair += ",";
    }
    new_pair = new_pair + string(1, '"') + key + string(1, '"') + ":" + str_value + "}";
    // replace content on instance & add to vector
    this->content += new_pair;
    tuple<string, string> pair = make_tuple(key, str_value);
    this->pairs.push_back(pair);
    this->inserting_point = this->content.length()-2;
}

void JSONObject::append(string key, string value){
    // cast value to string
    string str_value = string(1, '"') + value + string(1, '"');
    // remove the last element: '}'
    this->content.pop_back();
    // create string pair to-insert
    string new_pair = "";
    if (this->inserting_point>0){
        new_pair += ",";
    }
    new_pair = new_pair + string(1, '"') + key + string(1, '"') + ":" + str_value + "}";
    // replace content on instance & add to vector
    this->content += new_pair;
    tuple<string, string> pair = make_tuple(key, str_value);
    this->pairs.push_back(pair);
    this->inserting_point = this->content.length()-2;
}

void JSONObject::append(string key, bool value){
    // cast value to string
    string str_value;
    if (value){
        str_value = "true";
    } else {
        str_value = "false";
    }
     // remove the last element: '}'
    this->content.pop_back();
    // create string pair to-insert
    string new_pair = "";
    if (this->inserting_point>0){
        new_pair += ",";
    }
    new_pair = new_pair + string(1, '"') + key + string(1, '"') + ":" + str_value + "}";
    // replace content on instance & add to vector
    this->content += new_pair;
    tuple<string, string> pair = make_tuple(key, str_value);
    this->pairs.push_back(pair);
    this->inserting_point = this->content.length()-2;
}

void JSONObject::append(string key, JSONObject value){
    // cast value to string
    string str_value = value.content;
    // remove the last element: '}'
    this->content.pop_back();
    // create string pair to-insert
    string new_pair = "";
    if (this->inserting_point>0){
        new_pair += ",";
    }
    new_pair = new_pair + string(1, '"') + key + string(1, '"') + ":" + str_value + "}";
    // replace content on instance & add to vector
    this->content += new_pair;
    tuple<string, string> pair = make_tuple(key, str_value);
    this->pairs.push_back(pair);
    this->inserting_point = this->content.length()-2;
}

void JSONObject::append(string key, JSONArray value){
    // cast value to string
    string str_value = value.content;
    // remove the last element: '}'
    this->content.pop_back();
    // create string pair to-insert
    string new_pair = "";
    if (this->inserting_point>0){
        new_pair += ",";
    }
    new_pair = new_pair + string(1, '"') + key + string(1, '"') + ":" + str_value + "}";
    // replace content on instance & add to vector
    this->content += new_pair;
    tuple<string, string> pair = make_tuple(key, str_value);
    this->pairs.push_back(pair);
    this->inserting_point = this->content.length()-2;
}   

void JSONObject::append(string key){
    // cast value to string
    string str_value = "null";
    // remove the last element: '}'
    this->content.pop_back();
    // create string pair to-insert
    string new_pair = "";
    if (this->inserting_point>0){
        new_pair += ",";
    }
    new_pair = new_pair + string(1, '"') + key + string(1, '"') + ":" + str_value + "}";
    // replace content on instance & add to instance
    this->content += new_pair;
    tuple<string, string> pair = make_tuple(key, str_value);
    this->pairs.push_back(pair);
    this->inserting_point = this->content.length()-2;
}

void JSONObject::remove(string key){
    string new_content = "{";
    // ^^^^ fill this string with current pairs(saved on the vector)
    //          and avoid the specified key
    vector< tuple<string, string> > new_pairs;
    // ^^NOTE^^: in the same loop the vector with the pairs will be reconstructed
    for (int i=0; i<this->pairs.size(); i++) {
        tuple <string, string> current = this->pairs[i];
        if (get<0> (current) != key){
            if (i>0) {
                new_content += ",";
            }
            new_pairs.push_back(current);
            new_content = new_content + string(1, '"') + get<0> (current) + string(1, '"') + 
                          ":" + get<1> (current);
        }
    }
    new_content += "}";
    // change the respective attributes
    this->content = new_content;
    this->pairs = new_pairs;
    this->inserting_point = this->content.length()-2;
}

bool JSONObject::check_if_repeated(string key){

}

void JSONObject::rebuild_content(){

}

// JSONArray methods
JSONArray::JSONArray() : inserting_point(0){
    this->content = "[]";
}

JSONArray::JSONArray(string jsonString){
    this->content = jsonString;
    this->inserting_point = this->content.length()-2;
    // Read values saved in the string of the array
        // >> value-related: saving values in 'this->values'
    string n_value = "";
        // >> parsing json
    int subcase = 0;
    for (int i=0; i<jsonString.length(); i++){
        switch (jsonString[i]){
            case ']':
                if (subcase == 1){
                    subcase --;
                    n_value += string(1, jsonString[i]);
                } else if (subcase == 0){
                    if (n_value != ""){
                        this->values.push_back(n_value);
                        n_value = "";
                    }
                } else if (subcase > 1){
                    subcase--;
                    n_value += string(1, jsonString[i]);
                }
                break;

            case '}':
                if (subcase>0){
                    subcase--;
                }
                n_value += string(1, jsonString[i]);
                if (subcase == 0){
                    this->values.push_back(n_value);
                    n_value = "";
                }
                break;
            
            case ',':
                if (subcase>0){
                    n_value += string(1, jsonString[i]);
                }else if (subcase==0){
                    this->values.push_back(n_value);
                    n_value = "";
                }
                break;

            default:
                if ((jsonString[i]=='{' || (jsonString[i]=='[') && i>0)) {
                    subcase++;
                    n_value += string(1, jsonString[i]);
                } else if (i>0) {
                    n_value += string(1, jsonString[i]);
                }
                break;
        }
    }
}

int JSONArray::size(){
    return this->values.size();
}

string JSONArray::Get(int index){

}

int JSONArray::getInt(int index){
    int value;
    stringstream(this->values[index]) >> value;
    return value;
    
}

float JSONArray::getFloat(int index){
    float value;
    stringstream(this->values[index]) >> value;
    return value;
}

string JSONArray::getString(int index){
    if (this->values[index][0]=='"' && this->values[index][this->values[index].length()-1]=='"'){
        string retrn = "";
        for (int i=1; i<this->values[index].length()-1; i++){
            retrn += string(1, this->values[index][i]);
        }
        return retrn;
    } else {
        return "!!!";
    }
}

bool JSONArray::getBool(int index){
    if (this->values[index] == "true"){
        return true;
    } else if (this->values[index]== "false"){
        return false;
    } else{
        return NULL;
    }
}

bool JSONArray::isNull(int index){
    return false;
}

JSONObject JSONArray::getObject(int index){
    return JSONObject(this->values[index]);
}

JSONArray JSONArray::getArray(int index){
    return JSONArray(this->values[index]);
}

void JSONArray::append(int value){
    // cast value to string
    string str_value = to_string(value);
    // remove last element last element: ']'
    this->content.pop_back();
    // add the new value to the list & add to vector
    this->content += ("," + str_value + "]");
    this->values.push_back(str_value);
    this->inserting_point = this->content.length()-2;
}

void JSONArray::append(float value){
    // cast value to string
    string str_value = to_string(value);
    // remove last element last element: ']'
    this->content.pop_back();
    // add the new value to the list & add to vector
    this->content += ("," + str_value + "]");
    this->values.push_back(str_value);
    this->inserting_point = this->content.length()-2;
}

void JSONArray::append(string value){
    // cast value to string
    string str_value = string(1, '"') + value + string(1,'"');
    // remove last element last element: ']'
    this->content.pop_back();
    // add the new value to the list & add to vector
    this->content += ("," + str_value + "]");
    this->values.push_back(str_value);
    this->inserting_point = this->content.length()-2;
}

void JSONArray::append(bool value){
    // cast value to string
    string str_value = "";
    if (value){
        str_value += "true";
    } else {
        str_value += "false";
    }
    // remove last element last element: ']'
    this->content.pop_back();
    // add the new value to the list & add to vector
    this->content += ("," + str_value + "]");
    this->values.push_back(str_value);
    this->inserting_point = this->content.length()-2;
}

void JSONArray::append(JSONObject value){
    // cast value to string
    string str_value = "";
    str_value += value.content;
    // remove last element last element: ']'
    this->content.pop_back();
    // add the new value to the list & add to vector
    this->content += ("," + str_value + "]");
    this->values.push_back(str_value);
    this->inserting_point = this->content.length()-2;
}

void JSONArray::append(JSONArray value){
    // cast value to string
    string str_value = value.content;
    // remove last element last element: ']'
    this->content.pop_back();
    // add the new value to the list & add to vector
    this->content += ("," + str_value + "]");
    this->values.push_back(str_value);
    this->inserting_point = this->content.length()-2;
}

void JSONArray::append(){
    // cast value to string
    string str_value = "null";
    // remove last element last element: ']'
    this->content.pop_back();
    // add the new value to the list & add to vector
    this->content += ("," + str_value + "]");
    this->values.push_back(str_value);
    this->inserting_point = this->content.length()-2;
}

void JSONArray::remove(int index){
    string new_content = "[";
    // ^^^^ fill this string with current pairs(saved on the vector)
    //          and avoid the specified key
    vector< string > new_values;
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
    this->inserting_point = this->content.length()-2;
}
