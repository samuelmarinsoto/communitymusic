#ifndef fJSON_H
#define fJSON_H

#include <fstream>
#include <sstream>
#include <string>

#include <cctype>
#include <algorithm>
#include <tuple>

#include <vector>
#include <type_traits>
#include <iomanip>

using namespace std; // simplies writing "std:: . . . "

class JSONArray;

class JSONObject{
    private:
        vector< tuple<string, string> > pairs;
        int inserting_point;

        bool check_if_repeated(string key); // checks if given key exists in vector
        void rebuild_content(); // rebuilds a string based on current pairs(if a value is changed)

    public:
        string content;
    // Usable constructors
        JSONObject(string jsonString);
        JSONObject();
    // >> Insertion methods
        void append(string key, int value);
        void append(string key, float value);
        void append(string key, string value);
        void append(string key, bool value);
        void append(string key, JSONObject value);
        void append(string key, JSONArray value);
        void append(string key);

    // >> Removal method
        void remove(string key);
        bool isNull(string key);

    // >> Generic data type retrieval
        string Get(string key);
        int getInt(string key);
        float getFloat(string key);
        string getString(string key);
        bool getBool(string key);

    // >> JSON variant data types
        JSONObject getObject(string key);
        JSONArray getArray(string key);

};

class JSONArray {
    private:
        vector< string > values;
        int inserting_point;
    public:
        string content;

        // Usable constructors
        JSONArray(string jsonString);
        JSONArray();

        // Insertion methods
        void append(int value);
        void append(float value);
        void append(string value);
        void append(bool value);
        void append(JSONObject value);
        void append(JSONArray value);
        void append();

        // >> Other methods
        int size();
        void remove(int index);
        bool isNull(int index);

        // >> Data retrieval methods
        string Get(int index);
        int getInt(int index);
        float getFloat(int index);
        string getString(int index);
        bool getBool(int index);

        // >> JSON variant types
        JSONObject getObject(int index);
        JSONArray getArray(int index);
};

std::string json_as_string(const std::string filePath);

#endif //fJSON_H