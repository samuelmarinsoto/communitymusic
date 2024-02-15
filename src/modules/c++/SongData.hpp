#ifndef SONGDATA_H
#define SONGDATA_H

#include <string>

class SongData {   
    public:
    //---------------[Class attributes]---------------//
        std::string ID;
        std::string name;
        std::string artist;
        std::string album;
        std::string genre;
        int upVotes;
        int downVotes;
        std::string path_ref;

    //---------------[Class methods]---------------//
        SongData(std::string song_path) : path_ref(song_path){};
};

#endif