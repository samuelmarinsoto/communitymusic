#include <iostream>
#include "LinkedList.hpp"
using namespace :: std;

struct nodo {
    int data;
    Node* next;
    Node* prev;
}*first, *last;

void insertSong();
void ShowSongs();
void ShowSongsBackwards();
int main(){
    return 0;
}

void insertSong(){
    Node* new= new Node();
    cout << "Enter the value to insert: ";
    cin >> new->data;
    if(first==NULL){
        first=new;
        last=first;
        first->next=first;
        first->prev=last;
    }else{
        last->next=new;
        new->prev=last;        
        new->next=first;
        last=new;
        first->prev=last;
    }
}
void ShowSongs(){
    Node* temp=new Node();
    temp=first;
    if(first!=NULL){
        do{
            cout << temp->data << " ";
            temp=temp->next;
        }while(temp!=first);
            cout << endl;
    }else{
        cout << "The list is empty";
    }
    cout << endl;
}
void ShowSongsBackwards();
    Node* temp=new Node();
    temp=last;
    if(first!=NULL){
        do{
            cout << temp->data << " ";
            temp=temp->prev;
        }while(temp!=last);
            cout << endl;
    }else{
        cout << "The list is empty";
    }
    cout << endl;
}
``` 