#include <iostream>
#include <crossguid/guid.hpp>
#include "Cancion.cpp"

int main(void){
	char archivo[25] = "smackdat.opus";
	Cancion cancion(archivo);

	cancion.printguid();
	std::cout << "titulo: " << cancion.titulo << std::endl;
	std::cout << "artista: " << cancion.artista << std::endl;
	std::cout << "album: " << cancion.album << std::endl;
	std::cout << "genero: " << cancion.genero << std::endl;
	std::cout << "tamaño: " << cancion.GetSize() << std::endl;
	return 0;
}
