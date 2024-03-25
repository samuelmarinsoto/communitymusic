// #include "SFML/Graphics.hpp"
// #include "SFML/Window.hpp"
#include "modules/c++/MP3Tags.hpp"
#include <iostream>
#include <string.h>

using namespace std;
// int main(int argc, char *argv[]){
int main(){ // Code testing
    MP3Tags cancion(string("/home/frederick/Desktop/bib/playlist1/Slipknot.mp3"));

    std::cout << cancion.file << std::endl;
    std::cout << cancion.title << std::endl;
    std::cout << cancion.artist << std::endl;
    std::cout << cancion.album << std::endl;
    std::cout << cancion.genre << std::endl;

    char* str_chars = new char[60];
    string str = "h e l l o ";
    strcpy(str_chars, str.c_str());
    str_chars[str.length()] = 'p';
    str_chars[str.length()+1] = '\0';

    string alf = string(str_chars);
    std::cout << alf << "\n" << alf.length() << std::endl;
    return 0;
}