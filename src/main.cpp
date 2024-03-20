#include "modules/c++/fJSON.hpp"
#include "modules/c++/Server.hpp"

#include <iostream>
#include <string>

int main(){

    Server socket(7676, "127.0.0.1");

    /*std::string jString = json_as_string("settings/file.json");
    JSONObject json(jString);
        json.remove("u");
        json.append("new", 41);
        json.append("a", 9);
    JSONArray arr = json.getArray("f");
        arr.append((float)67.81);
        arr.append(string("hello"));
        arr.remove(1);
    json.append("f",  arr);
    cout << json.content << endl;*/
    return 0;
}