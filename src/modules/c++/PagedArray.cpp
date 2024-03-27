
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

class PagedArray {
public:
	size_t size, objsize, rampages, pagesize, pagecount;
	char* filename;
	std::vector active_pages;
	
    PagedArray(size_t size_, size_t objsize_, size_t rampages_, size_t pagesize_ char* filename_){
    	size = size_;
    	objsize = objsize_;
    	rampages = rampages_;
    	strlcpy(filename_, filename, strlen(filename_)+1);
    	pagesize = pagesize_;
    	pagecount = (size*objsize)/pagesize;
 	
    	if (pagesize_%objsize_){
    		std::cerr << "Tamaño de pagina inadecuado para el objeto almacenado";
    		std::exit(EXIT_FAILURE);
    	}
    	
    	std::fstream file(*filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    	
    	if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir " << filename << " para uso en arreglo paginado\n";
            std::exit(EXIT_FAILURE);
        }
        
        // Resize the file to accommodate all pages
        file_.seekp((pagecount*pagesize) - 1);
        file_.put(0);
        file_.seekp(0);
    }

    ~PagedArray() {
        file_.close();
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

private:
    void loadPage(size_t pageIndex) {
        file_.seekg(pageIndex * pagesize);
        file_.read(reinterpret_cast<char*>(pages_.data()), pagesize);
    }

    void savePage(size_t pageIndex) {
        file_.seekp(pageIndex * pagesize);
        file_.write(reinterpret_cast<const char*>(pages_.data()), pagesize);
    }

    size_t size_;
    size_t page_count_;
    std::fstream file_;
    std::vector<char> pages_ = std::vector<char>(pagesize*pagecount);
    size_t currentPage_ = static_cast<size_t>(-1); // Invalid page index
};
