// Arquivo: ces11_ccqueue.h
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#ifndef CES11_CCQUEUE_H
#define CES11_CCQUEUE_H

#include <stdbool.h>

typedef struct c11List c11Queue;

c11Queue* c11qInit(int n, int elemSize);
void c11qFree(c11Queue* self);

int c11qSize(c11Queue* self);
bool c11qEmpty(c11Queue* self);

void* c11qFront(c11Queue* self);

void c11qPush(c11Queue* self, void* p);
void c11qPop(c11Queue* self);

#endif // CES11_CCQUEUE_H