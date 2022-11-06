#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;

}Age;

void printList(Age* n){
    while (n != NULL){
        printf("%d\t", n->data);
        n = n->next;
    }
}

int main(){
    Age *head;
    Age *sec;
    Age *third;
    Age *fourth;

    head = (Age*) malloc(sizeof(Age*));
    sec = (Age*) malloc(sizeof(Age*));
    third = (Age*) malloc(sizeof(Age*));
    fourth = (Age*) malloc(sizeof(Age*));

    head->data = 1;
    head->prev = NULL;
    head->next = sec;

    sec->data = 2;
    sec->prev = head;
    sec->next = third;

    third->data = 3;
    third->prev = sec;
    third->next = fourth;

    fourth->data = 4;
    fourth->prev = third;
    fourth->next = NULL;

    printList(head);
}
