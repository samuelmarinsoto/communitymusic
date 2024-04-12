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
#include "PagedArray.hpp"

// Private method definitions
void PagedArray::loadPage(size_t pageIndex) {
    file.seekg(pageIndex * pagesize);
    std::vector<MP3Tags> page;

    for (size_t i = 0; i < objs_per_page; i++) {
        MP3Tags cancion;
        file.read(cancion.uuid, 80);
        file.read(cancion.title, 50);
        file.read(cancion.artist, 50);
        file.read(cancion.album, 50);
        file.read(cancion.genre, 50);
        file.read(cancion.file, 100);
        file.read((char*)&cancion.upvotes, sizeof(int));
        file.read((char*)&cancion.downvotes, sizeof(int));
        page.push_back(cancion);
    }
    std::tuple<size_t, std::vector<MP3Tags>> tuple;
    std::get<0>(tuple) = pageIndex;
    std::get<1>(tuple) = page;

    push_front(tuple);
}

void PagedArray::savePage(std::tuple<size_t, std::vector<MP3Tags>>& savetuple) {
    file.seekp(std::get<0>(savetuple) * pagesize);
    std::vector<MP3Tags> cancionvec = std::get<1>(savetuple);

    for (size_t i = 0; i < objs_per_page; i++) {
        file.write(cancionvec[i].uuid, 80);
        file.write(cancionvec[i].title, 50);
        file.write(cancionvec[i].artist, 50);
        file.write(cancionvec[i].album, 50);
        file.write(cancionvec[i].genre, 50);
        file.write(cancionvec[i].file, 100);
        file.write((char*)&cancionvec[i].upvotes, sizeof(int));
        file.write((char*)&cancionvec[i].downvotes, sizeof(int));
    }
}

void PagedArray::push_front(std::tuple<size_t, std::vector<MP3Tags>>& newtuple) {
    // Save last active page to disk
    savePage(active_pages[active_pages.size() - 1]);
    // Move all elements one position to the right
    for (size_t i = active_pages.size() - 1; i > 0; --i) {
        active_pages[i] = std::move(active_pages[i - 1]);
    }

    // Insert the new item at the front
    active_pages[0] = newtuple;
}

void PagedArray::switch_front(std::tuple<size_t, std::vector<MP3Tags>>& switchtuple, int switchindex) {
    std::tuple<size_t, std::vector<MP3Tags>> temp = active_pages[0];
    active_pages[0] = switchtuple;
    active_pages[switchindex] = temp;
}

// Constructor definition
PagedArray::PagedArray(size_t size_, size_t objsize_, size_t rampages_, size_t pagesize_, char* filename_) {
    size = size_;
    objsize = objsize_;
    rampages = rampages_;
    filename = filename_;
    pagesize = pagesize_;

    if ((size * objsize) % pagesize)
        pagecount = (size * objsize) / pagesize + 1;
    else
        pagecount = (size * objsize) / pagesize;

    objs_per_page = pagesize / objsize;

    if (pagesize_ % objsize_) {
        LOG(INFO) << "Tamaño de pagina inadecuado para el objeto almacenado";
        std::exit(EXIT_FAILURE);
    }

    file.open(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        LOG(INFO) << "Error: No se pudo abrir " << filename << " para uso en arreglo paginado";
        std::exit(EXIT_FAILURE);
    }

    active_pages.resize(rampages);
    for (size_t i = 0; i < rampages; i++) {
        std::get<1>(active_pages[i]).resize(objs_per_page);
    }

    // Resize the file to accommodate all pages
    file.seekp((pagecount * pagesize) - 1);
    file.put(0);
    file.seekp(0);
}

// Destructor definition
PagedArray::~PagedArray() {
    file.close();
}

// Overloaded subscript operator definition
MP3Tags& PagedArray::operator[](size_t index) {
    size_t pageIndex = index / objs_per_page; 
    size_t pageOffset = index % objs_per_page;

    if (pageIndex >= pagecount) {
        LOG(INFO) << "Index out of bounds";
        std::exit(EXIT_FAILURE);
    }

    // Check if the page is loaded and if it's at the front of all other pages
    int pageloaded = 0;
    int ramindex = -1;
    for (size_t i = 0; i < active_pages.size(); i++) {
        if (std::get<0>(active_pages[i]) == pageIndex) {
            pageloaded = 1;
            ramindex = i;
            break;
        }
    }

    if (pageloaded) {
        // Move the page to the front if it wasn't already
        if (!(ramindex == 0))
            switch_front(active_pages[ramindex], ramindex);
    } else {
        loadPage(pageIndex);
    }

    return std::get<1>(active_pages[0])[pageOffset];
}

size_t PagedArray::getSize(){
    return this->size;
}
