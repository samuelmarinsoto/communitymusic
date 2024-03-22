#include "PagedArray.cpp"
#include "id3tags.cpp"

int main() {
    PagedArray pagedArray(20);
	char archivo[25] = "03 I say love.mp3";

    // Usage example
    for (size_t i = 0; i < 20-1; ++i) {
        pagedArray[i] = Cancion(archivo);
    }

	std::cout << "guid: " << pagedArray[15].guid << std::endl;
	std::cout << "titulo: " << pagedArray[15].titulo << std::endl;
	std::cout << "artista: " << pagedArray[15].artista << std::endl;
	std::cout << "album: " << pagedArray[15].album << std::endl;
	std::cout << "genero: " << pagedArray[15].genero << std::endl;
	std::cout << "tamaño: " << pagedArray[15].GetSize() << std::endl;
	return 0;
}
