#include <id3/tag.h>
#include <id3/field.h>
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

	Cancion(char * archivo){
		guid = xg::newGuid();
		mp3 = archivo;
		upvotes = 0;
		downvotes = 0;

		/* Se crea y desace una clase tag solo para extraer datos
		de mp3, la biblioteca no se usa para nada mas */
		ID3_Tag tag;
		tag.Link(archivo);

		// Le sacamos "frames" (campos) y guardamos texto en variables
		ID3_Frame* tframe = tag.Find(ID3FID_TITLE);
		if (tframe != NULL){
			titulo = const_cast<char*>(tframe->GetField(ID3FN_TEXT)->GetRawText());
		} else { std::cout << "No se pudo extraer titulo" << std::endl; }

		ID3_Frame* aframe = tag.Find(ID3FID_ORIGARTIST);
		if (aframe != NULL){
			artista = const_cast<char*>(aframe->GetField(ID3FN_TEXT)->GetRawText());
		} else { std::cout << "No se pudo extraer artista" << std::endl; }
		
		ID3_Frame* alframe = tag.Find(ID3FID_ALBUM);
		if (alframe != NULL){
			album = const_cast<char*>(alframe->GetField(ID3FN_TEXT)->GetRawText());
		} else { std::cout << "No se pudo extraer album" << std::endl; }
		
		ID3_Frame* gframe = tag.Find(ID3FID_CONTENTTYPE);
		if (gframe != NULL){
			genero = const_cast<char*>(gframe->GetField(ID3FN_TEXT)->GetRawText());
		} else { std::cout << "No se pudo extraer genero" << std::endl; }
		
	}
};
