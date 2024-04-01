#include <cstring>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include "MP3Tags.hpp"

using namespace std;

// Constructor definition
MP3Tags::MP3Tags(std::string mp3_path) {
    // GUID generation
    boost::uuids::random_generator gen;
    boost::uuids::uuid guid = gen();

    string uuid_string = boost::uuids::to_string(guid);
    strcpy(this->uuid, uuid_string.c_str());

    // Initialize the integers
    this->upvotes = 0;
    this->downvotes = 0;

    // Set the path into the buffer
    strcpy(this->file, mp3_path.c_str()); // copy file path as array into the required field

    // Metadata extraction
    TagLib::FileRef file(mp3_path.c_str());
    if (!file.isNull() && file.tag()) {
        TagLib::Tag* tag = file.tag(); // Get the tags
        // Set the tags into the object fields
        // Title
        std::string title_tag = tag->title().to8Bit(true);
        if (string(title_tag) == "") {
            title_tag = "Unknown";
        }
        strcpy(this->title, title_tag.c_str());
        // Artist
	    std::string artist_tag = tag->artist().to8Bit(true);
        if (artist_tag == "") {
            artist_tag = "Unknown";
        }
        strcpy(this->artist, artist_tag.c_str());
        // Album
        std::string album_tag = tag->album().to8Bit(true);
        if (string(album_tag) == "") {
            album_tag = "Unknown";
        }
        strcpy(this->album, album_tag.c_str());
        // Genre
        std::string genre_tag = tag->genre().to8Bit(true);
        if (string(genre_tag) == "") {
            genre_tag = "Unknown";
        }
        strcpy(this->genre, genre_tag.c_str());
    } else {
    	if (file.isNull())
    		cout << "Failed to open mp3 file\n" << endl;
    	if (!file.tag())
    		cout << "Could not extract metadata from mp3\n" << endl;
        // TODO: Should manage this error into the logs
    }
}

// Default constructor definition
MP3Tags::MP3Tags() {
    uuid[0] = '\0';
    title[0] = '\0';
    artist[0] = '\0';
    album[0] = '\0';
    genre[0] = '\0';
    file[0] = '\0';
    upvotes = 0;
    downvotes = 0;
}

// Destructor definition
MP3Tags::~MP3Tags() {
}
