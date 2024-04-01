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
#include <cmath>
#include <iostream>

using namespace std;
// Class for interacting with SFML resources
class Interface {
    // ----------------------------- ATTRIBUTES
private:
    DoubleLinkedList<MP3Tags> songs;
    CircularList<MP3Tags>* player;
    /*PagedArray pagedsongs;*/
protected:
    std::tuple<int, int> dimensions[2];
    sf::Font font;

    string playlist_path;
    string program_data_path;
    bool paged;

    Loader* loader;
    // ----------------------------- METHODS
public:
    // Creates an instance of the class which automatically runs window [A]
    Interface();
    ~Interface();
protected:
    // Replaces all occurrences of a char in a string for another specified char
    // Parameters:
    // char value: char to find
    // char new_value: char to place
    // string source: source string to modify
    void find_replace(char value, char new_value, string& source);
    // Loads all ini file properties into the dedicated attributes
    void Load_INI();
private:
    // Initializes the first window[A] of the app
    // This is the welcome window
    void InitWinA();
    // Initializes the second window[B] of the app for using {LinkedList} data type.
    // This is the main program window where the user can use the playlist functions
    void InitWinB1();
    // Initializes the second window[B] of the app for using {PagedArray} data type
    // This is the main program window where the user can use the playlist functions
    void InitWinB2();
    // Initializes the third window[C] of the app
    // This is the configurations window
    void InitWinC();
};

#endif // INTERFACE_HPP
