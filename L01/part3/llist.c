// Implement a double linked-list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

// Initialize the linked list by setting head to NULL
// PRE: head is the pointer variable that points to the
//      first node of the linked list
// POST: head is set to NULL

void init_llist(TLinkedList **head) {
    // Set head to NULL
    *head = NULL;
}

// Create a new node
// PRE: filename = name of file to be inserted
//      filesize = size of file in blocks
//      startblock = File's starting block
// RETURNS: A new node containing the file information is created.

TLinkedList *create_node(char *filename, int filesize, int startblock) {
    TLinkedList* nodePtr = (TLinkedList*)malloc(sizeof(TLinkedList));

    strcpy(nodePtr->filename, filename);
    nodePtr->filesize = filesize;
    nodePtr->startblock = startblock;
    nodePtr->prev = NULL;
    nodePtr->next = NULL;

    return nodePtr;
}

// Insert node into the end of the linkedlist indicated by head
// PRE: head = Pointer variable pointing to the start of the linked list
//      node = Node created using create_node
// POST: node is inserted into the linked list.

void insert_llist(TLinkedList **head, TLinkedList *node) {
    if(*head == NULL){
        *head = node;
        return;
    }

    TLinkedList* trav = *head;

    while(trav->next != NULL){
        trav = trav->next;
    }

    trav->next = node;
    node->prev = trav;
}

// Delete node from the linkedlist
// PRE: head = Pointer variable pointing to the start of the linked list
//      node = An existing node in the linked list to be deleted.
// POST: node is deleted from the linked list

void delete_llist(TLinkedList **head, TLinkedList *node) {
    if(node == *head){
        if(node->next == NULL){
            free(node);

            *head = NULL;
        } else{
            *head = node->next; //Set new head

            free(node); //Free old head

            (*head)->prev = NULL; //Since head
        }

        return;
    }

    if(node->next != NULL){ //If not last node...
        node->next->prev = node->prev;
    }

    node->prev->next = node->next; //No need to check node->prev for NULL as node != *head

    free(node);
}


// Find node in the linkedlist
// PRE: head = Variable that points to the first node of the linked list
//      fname = Name of file to look for
// RETURNS: The node that contains fname, or NULL if not found.
TLinkedList *find_llist(TLinkedList *head, char *fname) {
    TLinkedList* trav = head;

    while(trav != NULL){
        if(strcmp(trav->filename, fname) == 0){ //If same...
            return trav;
        }

        trav = trav->next;
    }

    return NULL;
}

// Traverse the entire linked list calling a function
// PRE: head = Variable pointing to the first node of the linked list
//      fn = Pointer to function to be called for each node
// POST: fn is called with every node of the linked list.

void traverse(TLinkedList **head, void (*fn)(TLinkedList *)) {
    TLinkedList* trav = *head;

    while(trav != NULL){
        fn(trav);
        trav = trav->next;
    }
}

