#include "modules/c++/LinkedList.hpp"
#include <iostream>

int main() {
    LinkedList<int> list;

    // Añadir elementos a la lista
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);

    // Imprimir la lista
    list.PrintList();

    // Eliminar un elemento de la lista
    list.deleteNode(2);

    // Imprimir la lista después de eliminar un elemento
    list.PrintList();

    return 0;
}