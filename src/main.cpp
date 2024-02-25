#include "modules/c++/fJSON.hpp"

#include <iostream>
#include <string>

int main(){
    std::string jString = json_as_string("settings/file.json");
    JSONObject json(jString);
        json.remove("u");
        json.append("new", 41);
    JSONArray arr = json.getArray("f");
        arr.append((float)67.81);
        arr.append(string("hello"));
        arr.remove(1);
    cout << arr.getFloat(2) << endl;
    return 0;
}