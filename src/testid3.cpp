#include <iostream>
#include "MP3Tags.hpp"

int main(void){
	std::string archivo;
	archivo = "musica/08. 目が覚めたら.mp3";
	MP3Tags cancion(archivo);

	std::cout << "titulo: " << cancion.title << std::endl;
	std::cout << "artista: " << cancion.artist << std::endl;
	std::cout << "album: " << cancion.album << std::endl;
	std::cout << "genero: " << cancion.genre << std::endl;
	return 0;
}
