#include "JSON_Dict.h"

Dictionary::Dictionary(){
    this->content = "{}";
}

Dictionary::Dictionary(string json_string){
    this->content = json_string;
    
    tuple<string, string> n_pair = make_tuple("",""); // tuple in which to save the key-value's
    string reading = ""; // string to save chars as they are read
                         // allows constructing the keys and values

    // Retrieve key-value pairs from the given string
    bool hasSeenKey = false;
    int case_count = 0;
    for ( int i=0 ; i<json_string.length() ; i++) {
        // key detection --> when " : " is spotted
        if (!hasSeenKey && json_string[i]==':'){
            hasSeenKey = true;
            get<0> (n_pair) = reading;
            reading = "";
            i++;
        }
        // value construction --> based on char case
        if (hasSeenKey){
            switch (json_string[i]){
                case '}':
                    // complete the value and save to tuple
                    if (case_count == 1){
                        case_count--;
                        reading += string(1, json_string[i]);
                        get<1> (n_pair) = reading;
                        reading = "";
                        this->pairs.push_back(n_pair);
                        n_pair = make_tuple("","");
                        hasSeenKey = false;
                    } else if (case_count == 0){
                        if (reading!="") {
                            get<1> (n_pair) = reading;
                            reading = "";
                            this->pairs.push_back(n_pair);
                            n_pair = make_tuple("","");
                            hasSeenKey = false;
                        }
                    } else if (case_count > 1){
                        case_count--;
                        reading += string(1, json_string[i]);
                    }
                    break;

                case ',':
                    // complete the value and save to tuple
                    if (case_count>0){
                        reading += string(1, json_string[i]);
                    }else if (case_count == 0){
                        get<1> (n_pair) = reading;
                        reading = "";
                        this->pairs.push_back(n_pair);
                        n_pair = make_tuple("","");
                        hasSeenKey = false;
                    }
                    break;
                
                case ']':
                    if (case_count>0){
                        case_count--;
                    }
                    reading += string(1, json_string[i]);
                    if (case_count == 0){
                        get<1> (n_pair) = reading;
                        reading = "";
                        this->pairs.push_back(n_pair);
                        n_pair = make_tuple("","");;
                        hasSeenKey = false;
                    }
                    break;
                default:
                    if (json_string[i]=='['){
                        case_count++;
                    } else if (json_string[i]=='{'){
                        case_count++;
                    }
                    reading += string(1, json_string[i]);
                    break;
            }
        }
        // key construction -> ignores most symbols except ":"
        if (!hasSeenKey && (json_string[i]!='{' && json_string[i]!='}' && json_string[i]!='[' && json_string[i]!=']' &&  json_string[i]!=',' && json_string[i]!='"')){
            reading += string(1,json_string[i]);
        }
    }
}

bool Dictionary::verify_existence(string key){
    for (int i = 0; i<this->pairs.size(); i++){
        if (get<0> (this->pairs[i]) == key){
            return true;
        }
    }
    return false;
}

void Dictionary::rebuild(){
    this->content = "{";
    tuple <string, string> pair;
    for (int i = 0; i<this->pairs.size() ; i++){
        pair = this->pairs[i];
        if (i != 0){
            this->content += ",";
        }
        this->content += (string(1, '"') + get<0> (pair) + string(1, '"') + ":" + get<1> (pair));
    }
    this->content +=  "}";
}

Value Dictionary::operator[](string key){
    for (int i = 0; i<this->pairs.size(); i++){
        if (get<0>(this->pairs[i])==key){
            return Value(get<1>(this->pairs[i]));
        }
    }
    if (this->pairs.size() == 1){
        return Value(get<1>(this->pairs[0]));
    }
    return Value("null");
}

void Dictionary::add(string key, Value value){
    if (this->verify_existence(key)){
        for (int i = 0; i<this->pairs.size(); i++){
            if (get<0>(this->pairs[i]) == key){
                //this->pairs.set(i, make_tuple(key, value.content));
                this->pairs[i] = make_tuple(key, value.content);
                break;
            }
        }
    } else {
        this->pairs.push_back(make_tuple(key, value.content));
    }
    this->rebuild();
}

void Dictionary::remove(string key){
    vector < tuple<string, string> > new_pairs;
    for (int i = 0; i<this->pairs.size(); i++){
        if (get<0>(this->pairs[i]) != key){
            new_pairs.push_back(this->pairs[i]);
        }
    }
    this->pairs = new_pairs;
    this->rebuild();
}

Dictionary::~Dictionary(){
    
}