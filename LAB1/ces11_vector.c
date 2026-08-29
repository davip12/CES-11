// Arquivo: ces11_vector.c
//
// [CES-11] T30.3: Lab01.I
// Davi Honorio de Brito Pontes
// 9389

#include "ces11_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // para usar memcpy;

struct c11vector
{
	void *data_;
	int elemSize_;
	int count_;
	int capacity_;
};
/**
 *  \brief malloc com checagem de erro
 *  
 *  \param [in] size tamanho da regiao de alocacao
 *  \return [void*] regiao alocada
 */
static void* safeMalloc(const size_t size)
{
    void * tmp = malloc(size);
    if (!tmp)
    {
        fprintf(stderr, "safeMalloc: Deu ruim, o malloc falhou");
        exit(EXIT_FAILURE);
    }
    return tmp;
}

/**
 *  \brief Aumenta a capacidade de um vetor
 *  
 *  \param [in] self vetor a ter a capacidade aumentada
 */
static void increaseCap(c11vector *self)
{
    if (self->count_ == self->capacity_)
    {
        if (self->capacity_ == 0) self->capacity_ = 2;
        else self->capacity_ *= 2;

        void *tmp = realloc(self->data_, self->capacity_ * self->elemSize_);
        if (!tmp)
        {
            fprintf(stderr, "deu ruim o realloc\n");
            exit(EXIT_FAILURE);
        }
        self->data_ = tmp;
    }
}
/**
 *  \brief Soma val ao contador de elementos do vetor.
 *  
 *  \param [c11vector*] self vetor a ter o contador alterado.
 *  \param [int] val valor a ser adiciondo ao contador (pode ser negativo).
 */
#define ADD_TO_SIZE(self, val) { if (self->count_ + val >= 0) self->count_ += val; }


c11vector* c11vInit(int elemSize , int n)
{
	c11vector* v = safeMalloc(sizeof(c11vector));
	
	v->data_ = safeMalloc(elemSize * n);
	v->elemSize_ = elemSize;
	v->count_ = 0;
	v->capacity_ = n == 0 ? 2 : n;

	return v;
}

void c11vFree(c11vector *self)
{
	if (self)
	{
		free(self->data_);
		free(self);
	}
}

void* c11vAt(c11vector *self, int i)
{
	if (!self)
	{
		fprintf(stderr, "c11vAt: argumento NULL");
		exit(EXIT_FAILURE);
	}
	
	// casting para char* para permitir aritmetica de ponteiros
	char* r = (char*) self->data_;
	// recastign para retornar
	return (void*) (r+i*self->elemSize_);
}

int c11vSize(c11vector* self)
{
	if (!self)
	{
		fprintf(stderr, "c11Size: argumento NULL");
		exit(EXIT_FAILURE);
	}
	return self->count_;
}

int c11vElemSize(c11vector* self)
{
	return self->elemSize_;
}

bool c11vEmpty(c11vector* self)
{
	return !c11vSize(self);
}

void* c11vInsert(c11vector* self, int pos)
{
	if (!self)
	{
		fprintf(stderr, "c11Insert: argumento NULL");
		exit(EXIT_FAILURE);
	}

	if (pos > c11vSize(self))
		increaseCap(self);
	
	// nao consegui pensar outro jeito senao usando memmove (string.h)
	// criando um buraco para inserir o novo elemento
	memmove(c11vAt(self, pos + 1), c11vAt(self, pos), (c11vSize(self) - pos) * self->elemSize_);
	
	ADD_TO_SIZE(self, 1);
	
	return c11vAt(self, pos);	
}

void* c11vPushBack(c11vector* self)
{
	if (!self)
	{
		fprintf(stderr, "c11vPushBack: argumento NULL");
		exit(EXIT_FAILURE);
	}
	
	increaseCap(self);
	
	void* r = c11vAt(self, c11vSize(self));
	ADD_TO_SIZE(self, 1);
	return r;
}
void c11vPopFront(c11vector* self)
{
	if (c11vEmpty(self))
		return;
	// ver cv11Insert
	memmove(c11vAt(self, 0), c11vAt(self, 1), (c11vSize(self) - 1) * self->elemSize_);
	
	ADD_TO_SIZE(self, -1);
}

void c11vPopBack(c11vector* self)
{
	if (c11vEmpty(self))
		return;
	ADD_TO_SIZE(self, -1);
}