
/*
REQ-S004 (15pts) La lista principal está paginada. El archivo .INI contiene los siguientes parámetros:
a. Activada o desactivada
b. Cantidad de páginas permitidas en memoria
c. Tamaño en bytes de cada página. Debe asegurarse que la cantidad de bytes sea exacta
para que quepan nodos completos. Cualquier valor incorrecto debe ser validado por el
programa
d. Ruta absoluta en el disco donde ocurre el swap
La paginación debe ser transparente, es decir, debe construir una clase llamada ListaPaginada que
implemente una interfaz ILista. Dicha interfaz provee operaciones tradicionales como add, delete,
search, getByIndex, entre otros. La paginación está totalmente encapsulada para el código que use
ListaPaginada.
ListaPaginada tiene un algoritmo de reemplazo LRU para reemplazar las páginas cargadas. El swap
ocurre en disco en la ruta configurada
La interfaz gráfica provee un toggle para activar o desactivar la paginación. Cuando se desactiva, se
carga nuevamente la lista de canciones completa a memoria. Cuando se activa, se libera el espacio de la
lista original y se carga la lista paginada.
La interfaz gráfica del servidor debe mostrar en todo momento, el consumo de memoria total de la
aplicación. Al activar o desactivar paginación, debe actualizarse apropiadamente. Si la memoria total no
se reduce, indicaría que la paginación no es correcta. El uso de memoria se puede validar utilizando el
monitor de procesos y memoria del sistema operativo.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "MP3Tags.hpp"

class PagedArray {
private:
	size_t size, objsize, rampages, pagesize, pagecount, objs_per_page, previndex;
	char* filename;
	std::vector<std::vector<MP3Tags>> active_pages;
	std::fstream file;
    size_t currentPage_ = static_cast<size_t>(-1); // Invalid page index

    void loadPage(size_t pageIndex) {
        file_.seekg(pageIndex * pagesize);
        std::vector<MP3Tags> page;

        for (i=0;i<objs_per_page;i++){
        	MP3Tags cancion();
        	file.read(cancion->uuid, 80);
        	file.read(cancion->title, 50);
        	file.read(cancion.artist, 50);
        	file.read(cancion->album, 50);
        	file.read(cancion->genre, 50);
        	file.read(cancion->file, 100);
        	file.read(cancion->upvotes, sizeof(int));
        	file.read(cancion->downvotes, sizeof(int));
        	page[i] = cancion;
        }
        push_front(page);

    void savePage(size_t pageIndex) {
        file_.seekp(pageIndex * pagesize);
        file_.write(reinterpret_cast<const char*>(pages_.data()), pagesize);
    }
    
    void push_front(std::vector<MP3Tag>& newpage) {
        // Move all elements one position to the right
        for (size_t i = active_pages.size() - 1; i > 0; --i) {
            active_pages[i] = std::move(vec[i - 1]);
        }
    
        // Insert the new item at the front
        active_pages[0] = newpage;
    }

public:
    PagedArray(size_t size_, size_t objsize_, size_t rampages_, size_t pagesize_ char* filename_){
    	size = size_;
    	objsize = objsize_;
    	rampages = rampages_;
    	strlcpy(filename_, filename, strlen(filename_)+1);
    	pagesize = pagesize_;
    	pagecount = (size*objsize)/pagesize;
    	objs_per_page = pagesize/objsize;
 	
    	if (pagesize_%objsize_){
    		std::cerr << "Tamaño de pagina inadecuado para el objeto almacenado";
    		std::exit(EXIT_FAILURE);
    	}
    	
    	std::fstream file(*filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    	
    	if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir " << filename << " para uso en arreglo paginado\n";
            std::exit(EXIT_FAILURE);
        }

        active_pages = std::vector<std::vector<MP3Tags>(objs_per_page)>(rampages);
        
        // Resize the file to accommodate all pages
        file.seekp((pagecount*pagesize) - 1);
        file.put(0);
        file.seekp(0);
    }

    ~PagedArray() {
        file.close();
    }

    int& operator[](size_t index) {
        size_t pageIndex = index / pagesize;
        size_t pageOffset = index % pagesize;

        if (pageIndex >= pagecount) {
            std::cerr << "Index out of bounds\n";
            std::exit(EXIT_FAILURE);
        }

        // Load the page into memory if not already loaded
        if (currentPage_ != pageIndex) {
            loadPage(pageIndex);
            currentPage_ = pageIndex;
        }

        return pages_[pageOffset];
    }
};
