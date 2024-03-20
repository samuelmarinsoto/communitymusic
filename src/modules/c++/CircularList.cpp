// #include <iostream>
// #include "LinkedList.hpp"
// using namespace :: std;
// #include "Node.hpp"
// // struct nodo {
// //     int data;
// //     Node* next;
// //     Node* prev;
// // }*first, *last;

// void insertSong();
// void ShowSongs();
// void ShowSongsBackwards(); // corrected declaration

// int main(){
//     return 0;
// }

// void insertSong() {
//     Node* newNode = new Node(); // corrected variable name
//     cout << "Enter the value to insert: ";
//     cin >> newNode->data;
//     if (first == nullptr) {
//         first = newNode;
//         last = first;
//         first->next = first;
//         first->prev = last;
//     } else {
//         last->next = newNode;
//         newNode->prev = last;
//         newNode->next = first;
//         last = newNode;
//         first->prev = last;
//     }
// }

// void ShowSongs() {
//     Node* temp = first;
//     if (first != nullptr) {
//         do {
//             cout << temp->data << " ";
//             temp = temp->next;
//         } while (temp != first);
//         cout << endl;
//     } else {
//         cout << "The list is empty";
//     }
//     cout << endl;
// }

// void ShowSongsBackwards() { // corrected function definition
//     Node* temp = last;
//     if (first != nullptr) {
//         do {
//             cout << temp->data << " ";
//             temp = temp->prev;
//         } while (temp != first);
//         cout << endl;
//     } else {
//         cout << "The list is empty";
//     }
//     cout << endl;
// }
