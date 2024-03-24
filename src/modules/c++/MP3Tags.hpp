#ifndef MP3TAGS_H
#define MP3TAGS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <id3/tag.h>
#include <id3/field.h>
#include <id3/misc_support.h>
// si esa perra id3lib no funca use esto https://github.com/larsbs/id3v2lib?tab=readme-ov-file#api
#include <crossguid/guid.hpp>
// Object for extracting mp3 metadata(id3) into readable information in program
class MP3Tags{
	public:
		xg::Guid guid;
		char* title;
		char* artist;
		char* album; 
		char* genre;
		char* file; // "archivo"
		int upvotes, downvotes;
		// Creates an instance of an MP3Tags object by extracting the information from the file(via its path)
		MP3Tags(char* mp3_path){
			guid = xg::newGuid(); // Assign id
			upvotes = 0;
			downvotes = 0;
			// >> Set file path into file-field for object
			file = (char*)malloc(100);
			strlcpy(file, mp3_path, strlen(file));
			
			// Metadata extraction
			ID3_Tag tag;
				tag.Link(mp3_path);

			title = (char*)malloc(100);
			char* title_tag = ID3_GetTitle(&tag);
			strlcpy(title, title_tag, strlen(title));
			
			artist = (char*)malloc(100);
			char* artist_tag = ID3_GetArtist(&tag);
			strlcpy(artist, artist_tag, strlen(artist));
			
			album = (char*)malloc(100);
			char* album_tag = ID3_GetAlbum(&tag);
			strlcpy(album, album_tag, strlen(album));
			
			genre = (char*)malloc(100);
			char* genre_tag = ID3_GetGenre(&tag);
			strlcpy(genre, genre_tag, strlen(genre));
		}
		// Destroys the object and all its contents		
		~MP3Tags(){
			free(title);
			free(artist);
			free(album);
			free(genre);
			free(file);
		}
		// Returns the byte size of the object with all its elements
		size_t GetSize(){
			return 100*5 + 4*2 + sizeof(this->guid);
		}
};

#endif // MP3TAGS_H