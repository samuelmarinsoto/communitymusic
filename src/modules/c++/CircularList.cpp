#include <iostream>
#include "LinkedList.hpp"
using namespace :: std;

struct nodo {
    int data;
    Node* next;
}*first, *last;

void insertSong();

int main(){
    return 0;
}

void insertSong(){
    Node* new= new Node();
    cout << "Enter the value to insert: ";
    cin >> new->data;
    if(first==NULL){
        first=new;
        first->next=first;
        last=first;
    }else{
        last->next=new;
        new->next=first;
        last=new;
    }
}

void ShowSongs(){
    Node* temp=first;
    do{
        cout << temp->data << " ";
        temp=temp->next;
    }while(temp!=first);
    cout << endl;
}
```