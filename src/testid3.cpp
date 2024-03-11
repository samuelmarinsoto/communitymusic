#include <iostream>
#include <crossguid/guid.hpp>
#include "id3tags.cpp"

int main(void){
	char archivo[25] = "03 I say love.mp3";
	Cancion cancion(archivo);

	std::cout << "guid: " << cancion.guid << std::endl;
	std::cout << "titulo: " << cancion.titulo << std::endl;
	std::cout << "artista: " << cancion.artista << std::endl;
	std::cout << "album: " << cancion.album << std::endl;
	std::cout << "genero: " << cancion.genero << std::endl;
	return 0;
}
