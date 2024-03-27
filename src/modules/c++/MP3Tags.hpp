#ifndef MP3TAGS_H
#define MP3TAGS_H

#include <cstring> // For strcpy
#include <iostream>
// For GUID
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
// For tag retrieval
#include <taglib/tag.h>
#include <taglib/fileref.h>

using namespace std;
// C++ class implementation to extract the id3 metadata of mp3 files
class MP3Tags {
public:
    char uuid[80];
    char title[50];
    char artist[50];
    char album[50];
    char genre[50];
    char file[100];
    int upvotes, downvotes;

	// Loads the tags of a song into an object for use in the program
    MP3Tags(std::string mp3_path) {
		// GUID generation
		boost::uuids::random_generator gen;
		boost::uuids::uuid guid = gen();

		string uuid_string = boost::uuids::to_string(guid);
		strcpy(this->uuid, uuid_string.c_str());

		// Initialized the integers
        this->upvotes = 0;
        this->downvotes = 0;

		// Set the path into the buffer
		strcpy(this->file, mp3_path.c_str()); // copy file path as array into the required field

		// Metadata extraction
		TagLib::FileRef file(mp3_path.c_str());
		if (!file.isNull() && file.tag()){
			TagLib::Tag *tag = file.tag(); // Get the tags
			// Set the tags into the object fields
			// Title
			const char* title_tag = tag->title().toCString(true);
			if (string(title_tag) == ""){
				title_tag = "Unknown";
			}
			strcpy(this->title , title_tag);
			// Artist
			const char* artist_tag = tag->artist().toCString(true);
			if (string(artist_tag) == ""){
				artist_tag = "Unknown";
			}
			strcpy(this->artist , artist_tag);
			// Album
			const char* album_tag = tag->album().toCString(true);
			if (string(album_tag) == ""){
				album_tag = "Unknown";
			}
			strcpy(this->album , album_tag);
			// Genre
			const char* genre_tag = tag->genre().toCString(true);
			if (string(genre_tag) == ""){
				genre_tag = "Unknown";
			}
			strcpy(this->genre , genre_tag);
		} else {
			// TODO: Should manage this error into the logs
			cout << "Failed to open mp3" << endl;
		}

    }
	// Destroys the object and all its contents		
	~MP3Tags(){

	}
	// Returns the byte size of the object with all its elements
	size_t GetSize(){
		// TOTAL BYTE SIZE: file[100] + tags[50]*4 + uuid[80] + int[4]*2
		//return sizeof(char[101]) + sizeof(char[50])*4 + sizeof(char[80]) + sizeof(int)*2;
		return sizeof(*this);
	}
	// Operator for comparing two MP3Tags instances correctly
	// Compares check that the uuids are indeed different
	bool operator==(MP3Tags other){
		if(string(this->uuid) == string(other.uuid)){
			return true;
		}
		return false;
	}
};

#endif // MP3TAGS_H