#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <id3/tag.h>
#include <id3/field.h>
#include <id3/misc_support.h>
// si esa perra id3lib no funca use esto https://github.com/larsbs/id3v2lib?tab=readme-ov-file#api
#include <uuid/uuid.h>

class Cancion {
public:
	uuid_t guid;
	char* titulo;
	char* artista;
	char* album;
	char* genero;
	char* archivo;
	int upvotes, downvotes;

	Cancion(char* mp3){
		uuid_generate_random(guid);
		
		upvotes = 0;
		downvotes = 0;

		archivo = (char*)malloc(100);
		strlcpy(archivo, mp3, strlen(mp3)+1);
		
		/* Se crea y desace una clase tag solo para extraer datos
		de mp3, la biblioteca no se usa para nada mas */
		ID3_Tag tag;
		tag.Link(mp3);

		// Le sacamos "frames" (campos) y guardamos texto en variables
		titulo = (char*)malloc(100);
		char* titulo_ = ID3_GetTitle(&tag);
		strlcpy(titulo, titulo_, strlen(titulo_)+1);
		
		artista = (char*)malloc(100);
		char* artista_ = ID3_GetArtist(&tag);
		strlcpy(artista, artista_, strlen(artista_)+1);
		
		album = (char*)malloc(100);
		char* album_ = ID3_GetAlbum(&tag);
		strlcpy(album, album_, strlen(album_)+1);
		
		genero = (char*)malloc(100);
		char* genero_ = ID3_GetGenre(&tag);
		strlcpy(genero, genero_, strlen(genero_)+1);
	}
	
	~Cancion(){
		free(titulo);
		free(artista);
		free(album);
		free(genero);
		free(archivo);
	}

	size_t GetSize(){
		return 100*5 + sizeof(int)*2 + sizeof(uuid_t);
	}
	
	void printguid(){
		printf("guid: %08x-%04x-%04x-%04x-%012x\n", this->guid);
	}
};
