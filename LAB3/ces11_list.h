// Arquivo: ces11_list.h
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#ifndef CES11_LIST_H
#define CES11_LIST_H

#include <stdbool.h>

// Lista circular contígua
typedef struct c11List c11List;

c11List* c11lInit(int n, int elemSize);
void c11lFree(c11List* self);

void* c11lFront(c11List* self);
void* c11lBack(c11List* self);

void* c11lAt(c11List* self, int  pos);
bool c11lEmpty(c11List* self);

void* c11lInsert(c11List* self, int pos);
void c11lErase(c11List* self, int pos);

void* c11lPushFront(c11List* self);
void* c11lPushBack(c11List* self);
void* c11lPopFront(c11List* self);
void c11lPopBack(c11List self);

#endif // LIST_H
