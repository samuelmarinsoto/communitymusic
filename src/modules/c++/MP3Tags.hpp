#ifndef MP3TAGS_H
#define MP3TAGS_H

#include <cstdlib> // For malloc and free
#include <cstring> // For strcpy
#include <id3/tag.h>
#include <id3/field.h>
#include <id3/utils.h>
#include <id3/misc_support.h>
#include <guid.h> // Assuming it's the correct header for Crossguid

// C++ class implementation to extract the id3 metadata of mp3 files
class MP3Tags {
public:
    Guid guid;
    char *title;
    char *artist;
    char *album;
    char *genre;
    char *file;
    int upvotes, downvotes;

    MP3Tags(std::string mp3_path) {
        this->guid = Guid(); // Initialize to an empty GUID

		// Initialized the integers
        this->upvotes = 0;
        this->downvotes = 0;

        // Allocate all values in memory
		this->file = new char[101]; // fixed size(also maximum) is 101 bytes(1 byte = 1 char)
			strcpy(this->file, mp3_path.c_str()); // copy file path as array into the required field
		this->title = new char[50];
		this->artist = new char[50];
		this->album = new char[50];
		this->genre = new char[50];

        // Metadata extraction
        ID3_Tag* extractor = new ID3_Tag(); // Create as a pointer, the remove from memory
        if (extractor->Link(this->file)) { // Set tags into fields if found
			strcpy(this->title, ID3_GetTitle(extractor));
			strcpy(this->artist, ID3_GetArtist(extractor));
			strcpy(this->album, ID3_GetAlbum(extractor));
			strcpy(this->genre, ID3_GetGenre(extractor));

        } else { // set tags as error if file couldnt be read
			std::string id3_error = "Error-unknown";
			strcpy(this->title, id3_error.c_str());
            strcpy(this->artist, id3_error.c_str());
            strcpy(this->album, id3_error.c_str());
            strcpy(this->genre, id3_error.c_str());
        }
        delete extractor; // Removal of the metadata extractor
    }
	// Destroys the object and all its contents		
	~MP3Tags(){
		delete[] title;
		delete[] artist;
		delete[] album;
		delete[] genre;
		delete[] file;
	}
	// Returns the byte size of the object with all its elements
	size_t GetSize(){
		return 100*5 + 4*2 + sizeof(this->guid);
	}
};

#endif // MP3TAGS_H