// Arquivo : ces11_pqueue.c
//
// [CES-11] T30.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ces11_pqueue.h"
#include "ces11_vector.h"

c11pqueue* c11pqInit(int elemSize)
{
	return c11vInit(elemSize, 0);
}

void c11pqFree(c11pqueue *self)
{
	c11vFree(self);
}

bool c11pqEmpty(c11pqueue *self)
{
	return c11vEmpty(self);
}

int c11pqSize(c11pqueue *self)
{
	return c11vSize(self);
}


void c11pqPush(c11pqueue *self, void *q, int (*compare)(void*, void*))
{
	assert(self);
	assert(q);
	assert(compare);
	
	if (c11vEmpty(self))
	{
		void* elem = c11vPushBack(self);
		memcpy(elem, q, c11vElemSize(self));
		return;
	}
	
	// encontrar a posicao para inserir no vetor
	bool achou = false;
	int meio, cima, baixo, pos = 0;
	
	baixo = 0;
	cima = c11vSize(self)-1;
	while(baixo <= cima && cima >= 0 && !achou)
	{
		meio = (cima - baixo)/2 + baixo;
		
		if (compare(c11vAt(self, meio), q) > 0)
		{
			 cima = meio-1;
			 pos = meio;
		}
		else if (compare(c11vAt(self, meio), q) < 0)
		{
			 baixo = meio+1;
			 pos = baixo;
		}
		else
		{
			pos = meio;
			achou = true;
		}
	}
	// inserir o elemento q no vetor
	// aqui 'pos' e' a posicao em que deve ser adicionado q
	void* elem = c11vInsert(self, pos);
	memcpy(elem, q, c11vElemSize(self));
}

void c11pqPop(c11pqueue *self)
{
	c11vPopBack(self);
}

void* c11pqTop(c11pqueue *self)
{
	return c11vAt(self, c11vSize(self)-1);
}