#include "modules/c++/Node.hpp"
#include "modules/c++/SongData.hpp"

#include <iostream>

int main(){
    Node<SongData> node("path/to/mp3");
    std::cout << node.content.path_ref << std::endl;
};