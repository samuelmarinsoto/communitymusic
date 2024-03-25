// #include "SFML/Graphics.hpp"
// #include "SFML/Window.hpp"
#include "modules/c++/MP3Tags.hpp"
#include <iostream>
#include <string.h>

using namespace std;
// int main(int argc, char *argv[]){
int main(){ // Code testing
    MP3Tags cancion(string("/home/frederick/Desktop/bib/playlist1/System_Of_A_Down.mp3"));

    std::cout << "MP3 path: " << cancion.file << std::endl;
    std::cout << "Generated UUID: " << cancion.uuid << std::endl;
    std::cout << "Song name: " << cancion.title << std::endl;
    std::cout << "Artist: " << cancion.artist << std::endl;
    std::cout << "Album: " << cancion.album << std::endl;
    std::cout << "Genre: " << cancion.genre << std::endl;
    std::cout << "Total size(bytes): " << cancion.GetSize() << std::endl;

    MP3Tags cancion2(string("/home/frederick/Desktop/bib/playlist1/Slipknot.mp3"));

    std::cout << "MP3 path: " << cancion2.file << std::endl;
    std::cout << "Generated UUID: " << cancion2.uuid << std::endl;
    std::cout << "Song name: " << cancion2.title << std::endl;
    std::cout << "Artist: " << cancion2.artist << std::endl;
    std::cout << "Album: " << cancion2.album << std::endl;
    std::cout << "Genre: " << cancion2.genre << std::endl;
    std::cout << "Total size(bytes): " << cancion.GetSize() << std::endl;

    return 0;
}