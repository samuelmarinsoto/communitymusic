#ifndef INTERFACE_HPP
#define INTERFACE_HPP

// ----------------------------- Project modules
#include "../modules/c++/DoubleLinkedList.hpp"
#include "../modules/c++/CircularList.hpp"
#include "../modules/c++/MP3Tags.hpp"
#include "../modules/c++/MP3_to_WAV.h"

// ----------------------------- SFML Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

// ----------------------------- Other libraries
#include <tuple>
#include <vector>
#include <string>
#include <random>

using namespace std;
// Class for interacting with SFML resources
class Interface {
    // ----------------------------- ATTRIBUTES
protected:
    std::tuple<int, int> dimensions[2];
    sf::Font font;

    string playlist_path;
    string program_data_path;

    DoubleLinkedList<MP3Tags> songs;
    CircularList<MP3Tags>* player;
    Loader* loader;
    /*PagedArray pagedsongs;*/
    // ----------------------------- METHODS
public:
    // Creates an instance of the class which automatically runs window [A]
    Interface();
    ~Interface();
private:
    // Initializes the first window[A] of the app
    // This is the welcome window
    void InitWinA();
    // Initializes the second window[B] of the app
    // This is the main program window where the user can use the playlist functions
    void InitWinB();
    // Initializes the third window[C] of the app
    // This is the configurations window
    void InitWinC();
};

#endif // INTERFACE_HPP
