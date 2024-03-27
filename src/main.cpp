#include "modules/c++/DoubleLinkedList.h"
#include "modules/c++/CircularList.h"
#include "modules/c++/MP3_to_WAV.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>

using namespace std;
namespace fs = boost::filesystem;
// int main(int argc, char *argv[]){
int main(){ // Code testing
    // ------- Create the loader
    Loader loader(string("/home/frederick/Desktop/bib/.cmp"));

    // ------ Create a list of songs
        // Filenames retrieval
    string songs_path = "/home/frederick/Desktop/bib/playlist1";
    vector< string > filenames;
    try {
        fs::directory_iterator end_iter;
        for (fs::directory_iterator iter(songs_path); iter != end_iter; ++iter) {
            if (fs::is_regular_file(*iter)) {
                std::cout << "File: " << iter->path().filename() << std::endl;
                filenames.push_back(iter->path().filename().string());
            }
            // You can add more conditions for other types of entries if needed
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
        // List creation
    DoubleLinkedList<MP3Tags> songs;
        songs.InsertAtEnd(MP3Tags(songs_path + "/" + filenames[0]));
        songs.InsertAtEnd(MP3Tags(songs_path + "/" + filenames[1]));
        songs.InsertAtEnd(MP3Tags(songs_path + "/" + filenames[2]));
        songs.InsertAtEnd(MP3Tags(songs_path + "/" + filenames[3]));
    
    // Convert one of the songs to a wav
    loader.Convert(string(songs.GetNode(0)->data.file), string("current"));

    // Load and play the song
    sf::Music player;
    if (!player.openFromFile("/home/frederick/Desktop/bib/.cmp/current.wav")){
        std::cout << "Player failed!" << std::endl;
        return -1;
    }

    std::cout << "Playing" << std::endl;
    player.play();
    while (player.getStatus() == sf::Music::Playing){}

    std::cout << "Song finished" << std::endl;
    return 0;
}