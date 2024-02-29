#include <stdio.h>
#include <stdlib.h>

// Define a simple Nodo structure
struct Nodo {
    int data;
    struct Nodo* next;
};

// Function to save a portion of the linked list to a file
void saveToFile(struct Nodo* start, struct Nodo* end, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    struct Nodo* current = start;
    while (current != end->next) {
        fwrite(&current->data, sizeof(current->data), 1, file);
        current = current->next;
    }

    fclose(file);
}

// Function to load data from a file and append it to the linked list
void loadFromFile(struct Nodo** head, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    int value;
    while (fread(&value, sizeof(value), 1, file) == 1) {
        struct Nodo* newNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
        if (!newNodo) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        newNodo->data = value;
        newNodo->next = NULL;

        if (*head == NULL) {
            *head = newNodo;
        } else {
            struct Nodo* current = *head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNodo;
        }
    }

    fclose(file);
}

// Function to free the linked list
void freeList(struct Nodo* head) {
    while (head) {
        struct Nodo* toDelete = head;
        head = head->next;
        free(toDelete);
    }
}

void printList(struct Nodo* start){
	struct Nodo* head = start;
	while (head){
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

int main() {
    // Create a linked list
    struct Nodo* head = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (!head) {
        perror("Memory allocation error");
        return EXIT_FAILURE;
    }
    head->data = 1;
    head->next = (struct Nodo*)malloc(sizeof(struct Nodo));
    head->next->data = 2;
    head->next->next = (struct Nodo*)malloc(sizeof(struct Nodo));
    head->next->next->data = 3;
    head->next->next->next = NULL;

    printList(head);

    // Save a portion of the list to a file
    saveToFile(head, head->next, "data_chunk.bin");

    // Clear the portion of the list from memory (simulate swapping out)
    struct Nodo* temp = head->next;
    head->next = NULL;
    freeList(temp);
    
	printList(head);
	
    // Load the data from the file and append it back to the list (simulate swapping in)
    loadFromFile(&head, "data_chunk.bin");

    // Use the updated linked list
	printList(head);
	
    // Free the entire list and exit
    freeList(head);

    return EXIT_SUCCESS;
}
