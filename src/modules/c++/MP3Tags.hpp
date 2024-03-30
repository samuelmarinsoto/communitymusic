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

    MP3Tags(std::string mp3_path);
    MP3Tags();
	~MP3Tags();
};
