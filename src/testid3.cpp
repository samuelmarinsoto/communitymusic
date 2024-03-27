#include <iostream>
#include <crossguid/guid.hpp>
#include "modules/c++/MP3Tags.hpp"

int main(void){
	std::string archivo;
	archivo = "smackdat.mp3";
	MP3Tags cancion(archivo);

	std::cout << "titulo: " << cancion.title << std::endl;
	std::cout << "artista: " << cancion.artist << std::endl;
	std::cout << "album: " << cancion.album << std::endl;
	std::cout << "genero: " << cancion.genre << std::endl;
	// std::cout << "tamaño: " << cancion.GetSize() << std::endl;
	return 0;
}
