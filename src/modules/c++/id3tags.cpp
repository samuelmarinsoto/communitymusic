#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <id3/tag.h>
#include <id3/field.h>
#include <id3/misc_support.h>
// si esa perra id3lib no funca use esto https://github.com/larsbs/id3v2lib?tab=readme-ov-file#api
#include <crossguid/guid.hpp>

class Cancion {
public:
	xg::Guid guid;
	char* titulo;
	char* artista;
	char* album; 
	char* genero;
	char* archivo;
	int upvotes, downvotes;

	Cancion(char* mp3){
		guid = xg::newGuid();
		upvotes = 0;
		downvotes = 0;
		
		archivo = (char*)malloc(100);
		strlcpy(archivo, mp3, strlen(archivo));
		
		/* Se crea y desace una clase tag solo para extraer datos
		de mp3, la biblioteca no se usa para nada mas */
		ID3_Tag tag;
		tag.Link(mp3);

		// Le sacamos "frames" (campos) y guardamos texto en variables
		titulo = (char*)malloc(100);
		char* titulo_ = ID3_GetTitle(&tag);
		strlcpy(titulo, titulo_, strlen(titulo));
		
		artista = (char*)malloc(100);
		char* artista_ = ID3_GetArtist(&tag);
		strlcpy(artista, artista_, strlen(artista));
		
		album = (char*)malloc(100);
		char* album_ = ID3_GetAlbum(&tag);
		strlcpy(album, album_, strlen(album));
		
		genero = (char*)malloc(100);
		char* genero_ = ID3_GetGenre(&tag);
		strlcpy(genero, genero_, strlen(genero));
	}
	
	~Cancion(){
		free(titulo);
		free(artista);
		free(album);
		free(genero);
		free(archivo);
	}

	size_t GetSize(){
		return 100*5 + 4*2 + sizeof(this->guid);
	}
};