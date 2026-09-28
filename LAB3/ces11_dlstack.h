// Arquivo: ces11_dlstack.h
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#ifndef CES11_DLSTACK_H
#define CES11_DLSTACK_H

typedef struct c11Stack c11Stack;

c11Stack* c11sInit(int n, int elemSize);
void c11sFree(c11Stack* self);

int c11sSize(c11Stack* self);
bool c11sEmpty(c11Stack* self);

void* c11sTop(c11Stack* self);

void c11sPush(c11Stack* self, void* p);
void c11sPop(c11Stack* self);

#endif // CES11_STACK_H