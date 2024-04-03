#ifndef INTERFACE_HPP
#define INTERFACE_HPP

// ----------------------------- Project modules
#include "../modules/c++/PagedArray.hpp"
#include "../modules/c++/DoubleLinkedList.hpp"
#include "../modules/c++/CircularList.hpp"
#include "../modules/c++/MP3Tags.hpp"
#include "../modules/c++/MP3_to_WAV.h"
#include "../modules/c++/Server.h"

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
#include <fstream>
#include <iostream>
#include <exception>
#include <sstream>

using namespace std;
// Class for interacting with SFML resources
class Interface {
    // ----------------------------- ATTRIBUTES
private:
    // Song-related resources
    DoubleLinkedList<MP3Tags> songs;
    CircularList<MP3Tags>* player;
    PagedArray* songs_array;

    string playlist_path;
    string program_data_path;
    int PORT;
    bool paged_mode;
protected:
    std::tuple<int, int> dimensions[2];
    sf::Font font;
    Loader* loader;
    Server* user;
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
    // Write the current attributes 
    void Write_INI();
    // Loads 10 random songs file from the playlist directory into the songs list
    void Song_Selection();
    // Swaps the current list of songs to a paged array
    void LIST_TO_PAGED();
    // Swaps the current paged array of songs to a list
    void PAGED_TO_LIST();
    // Retuns the index position with the best voting difference (usable when using paged mode)
    int PAGED_getFollowing(PagedArray* origin_, vector<int>* disposed_);
    // Retuns TRUE if a index position has already been used, and FALSE otherwise(usable when using paged mode)
    bool PAGED_check_disposed(vector<int>* disposed_, int position);
    // Gets an array of all artists in the playlist with their songs in the current playlist
    void PAGED_getPlaylistArtists(string artists[], size_t size);
    // Gets all the current playlist songs of an specific artist
    vector<string> PAGED_getArtistSongs(string artist_name);
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
