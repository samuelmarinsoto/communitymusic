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
	char* mp3;
	int upvotes, downvotes;

	Cancion(){
		guid = xg::newGuid();
		mp3 = "03 I say love.mp3";
		upvotes = 0;
		downvotes = 0;

		/* Se crea y desace una clase tag solo para extraer datos
		de mp3, la biblioteca no se usa para nada mas */
		ID3_Tag tag;
		tag.Link("03 I say love.mp3");

		// Le sacamos "frames" (campos) y guardamos texto en variables
		titulo = ID3_GetTitle(&tag);
		artista = ID3_GetArtist(&tag);
		album = ID3_GetAlbum(&tag);
		genero = ID3_GetGenre(&tag);
		
	}
};
