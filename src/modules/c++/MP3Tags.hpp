#pragma once

#include <cstring>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <taglib/tag.h>
#include <taglib/fileref.h>

using namespace std;
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
  MP3Tags(std::string mp3_path);
  
  // Default constructor
  MP3Tags();
  
	// Destroys the object and all its contents		
	~MP3Tags();

	// Returns the byte size of the object with all its elements
	size_t GetSize();

	// Operator for comparing two MP3Tags instances correctly
	// Compares check that the uuids are indeed different
	bool operator==(MP3Tags other);
};
