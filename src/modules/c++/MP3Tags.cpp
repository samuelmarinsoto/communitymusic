#include "MP3Tags.hpp"

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
    if (!file.isNull() && file.tag()){
        TagLib::Tag *tag = file.tag(); // Get the tags
        // Set the tags into the object fields
        // Title
        string title_tag = tag->title().to8Bit(true);
        if (title_tag == ""){
            title_tag = "Unknown";
        }
        strcpy(this->title , title_tag.c_str());
        // Artist
        string artist_tag = tag->artist().to8Bit(true);
        if (artist_tag == ""){
            artist_tag = "Unknown";
        }
        strcpy(this->artist , artist_tag.c_str());
        // Album
        string album_tag = tag->album().to8Bit(true);
        if (album_tag == ""){
            album_tag = "Unknown";
        }
        strcpy(this->album , album_tag.c_str());
        // Genre
        string genre_tag = tag->genre().to8Bit(true);
        if (genre_tag == ""){
            genre_tag = "Unknown";
        }
        strcpy(this->genre , genre_tag.c_str());
    } else {
        LOG(INFO) << "MP3Tags.cpp: Failed to open mp3";
    }

}

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

MP3Tags::~MP3Tags() {

}

size_t MP3Tags::GetSize(){
    // TOTAL BYTE SIZE: file[100] + tags[50]*4 + uuid[80] + int[4]*2
    //return sizeof(char[101]) + sizeof(char[50])*4 + sizeof(char[80]) + sizeof(int)*2;
    return sizeof(*this);
}

bool MP3Tags::operator==(MP3Tags other){
    if(string(this->uuid) == string(other.uuid)){
        return true;
    }
    return false;
}
