#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*) malloc(sizeof(List));
    list->head=NULL;
    list->tail=NULL;
    list->current=NULL;
    return list;
}

void * firstList(List * list) {
    if (list == NULL){
      return NULL;
    }
    if (list->head == NULL){
      return NULL;
    }
    list->current = list->head;
    return (void *)list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL){
      return NULL;
    }
    if (list->current->next == NULL){
      return NULL;
    }
    list->current = list->current->next;
    return (void *)list->current->data;
}

void * lastList(List * list) {
    if (list == NULL){
      return NULL;
    }
    if (list->tail == NULL){
      return NULL;
    }
    list->current = list->tail;
    return (void *)list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL){
      return NULL;
    }
    if (list->current->prev == NULL){
      return NULL;
    }
    list->current = list->current->prev;
    return (void *)list->current->data;
}

void pushFront(List * list, const void * data) {
    Node* NodoNuevo = createNode(data);
    if (list->head == NULL){
      list->head = NodoNuevo;
      list->tail = list->head;
    }else{
      NodoNuevo->next = list->head;
      list->head->prev = NodoNuevo;
      list->head = NodoNuevo;
      NodoNuevo->prev = NULL;
    }
}

void pushBack(List * list, void const* data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
    Node* NodoNuevo = createNode(data);
    if (list->current->next == NULL){
      NodoNuevo->prev = list->current;
      list->current->next = NodoNuevo;
      list->current = NodoNuevo;
      list->tail = list->current;
    }else{
      NodoNuevo->prev = list->current;
      list->current->next = NodoNuevo;
      list->current = NodoNuevo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node* eliminado = (Node*)malloc(sizeof(Node));
    if (list->current->prev == NULL){
      eliminado = list->current;
      list->current = list->current->next;
      list->current->prev = NULL;
      return (void *)eliminado->data;
    }
    if (list->current->next == NULL){
      eliminado = list->current;
      list->current = list->current->prev;
      list->current->next = NULL;
      return (void *)eliminado->data;
    }

    //faltaba esto también
    return NULL;    
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}