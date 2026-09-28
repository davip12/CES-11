// Arquivo: ces11_ccqueue.c
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#include "ces11_list.h"
#include "ces11_ccqueue.h"

#include <stdio.h>
#include <string.h>

c11Queue* c11qInit(int n, int elemSize)
{
    return c11lInit(n, elemSize);
}
void c11qFree(c11Queue* self)
{
    c11lFree(self);
}

int c11qSize(c11Queue* self)
{
    return c11lSize(self);
}

bool c11qEmpty(c11Queue* self)
{
    return c11lEmpty(self);
}
void* c11qFront(c11Queue* self)
{
    return c11lFront(self);
}

void c11qPush(c11Queue* self, void* p)
{
	puts("c11qPush chamado!");
    void* q = c11lPushBack(self);
	puts("c11lPushBack ok");
    memmove(q, p, c11lElemSize(self));
	puts("memmove ok");
	puts("c11qPush ok");
}
void c11qPop(c11Queue* self)
{
    c11lPopFront(self);
}
