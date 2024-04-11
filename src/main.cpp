#include "app/c++/Interface.hpp"
#include "lib/fJSON.hpp"
#include <glog/logging.h>

int main(int argc, char* argv[]){
    google::InitGoogleLogging(argv[0]);
    Interface interface;
    // Dictionary dict;
    //     dict.add("key", JSON::convert_to_value<string>(string("hello")));

    // Array _j_array;
    //     _j_array.append(JSON::convert_to_value<Dictionary>(dict));
    //     _j_array.append(JSON::convert_to_value<float>(float(190.0056)));
    
    // std::cout << _j_array.content << std::endl;

    return 0;
}
