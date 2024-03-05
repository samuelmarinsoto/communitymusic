#include <iostream>
#include <crossguid/guid.hpp>
#include "id3tags.cpp"

int main(void){
	char archivo[25] = "03 I say love.mp3";
	Cancion cancion(archivo);

	std::cout << "guid: " << cancion.guid << std::endl;
	return 0;
}
