// Arquivo: ces11_list.c
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#include "ces11_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct c11List
{
	void* data_;
	void* head_;
	int size_;
	int capacity_;
	int elemSize_;
};

static void* safeMalloc(int bytes)
{
	void* tmp = malloc(bytes);
	if (!tmp)
	{
		fprintf(stderr, "Falha em alocar memoria para a lista.");
		exit(EXIT_FAILURE);		
	}
	return tmp;
}

c11List* c11lInit(int n, int elemSize)
{
	assert(n >= 0 && elemSize > 0);
	c11List* list =	safeMalloc(sizeof(c11List));

	list->elemSize_ = elemSize;
	list->capacity_ = (n <= 0 ? 2 : n);
	list->size_ = 0;
	
	list->data_ = safeMalloc(list->capacity_ * elemSize);
	list->head_ = list->data_;

	return list;
}

void c11lFree(c11List* self)
{
	if(self)
		free(self->data_);
	free(self);
}

bool c11lEmpty(c11List* self)
{
	return self->size_ == 0;
}

int c11lSize(c11List* self)
{
	return self->size_;
}

int c11lElemSize(c11List* self)
{
	return self->elemSize_;
}

void* c11lAt(c11List* self, int  pos)
{
	assert(self && pos >= -self->size_ && pos <= self->size_);
	int headPos = ((char*) self->head_ - (char*) self->data_) / self->elemSize_;
	if (headPos + pos >= self->capacity_)
		return (char*) self->data_ + (headPos + pos - self->capacity_) * self->elemSize_;
	else
		return (char*) self->head_ + pos * self->elemSize_;
}


void* c11lFront(c11List* self)
{
	return c11lAt(self, 0);
}

void* c11lBack(c11List* self)
{
	return c11lAt(self, self->size_ - 1);
}

void* c11lInsert(c11List* self, int pos)
{
	puts("c11lInsert chamado!");
	// Se a lista esta' cheia, aumenta a capacidade
	if (self->size_ == self->capacity_)
	{
		// Aloca uma nova regiao de memoria (maior) para a lista
		int newCap = self->capacity_ * 2;
		void* tmp = safeMalloc(newCap*self->elemSize_);

		// Copia a regiao antiga para a nova em 'chunks'
		int firstChunkBytes = ((char*)self->data_ + self->capacity_ * self->elemSize_) - ((char*)self->head_);
		int secondChunkBytes = ((char*) self->head_) - ((char*) self->data_);

		memmove(tmp, self->head_, firstChunkBytes);
		memmove(((char*) tmp) + firstChunkBytes, self->data_, secondChunkBytes);

		// Libera a regiao antiga
		free(self->data_);
		// Atualiza os campos
		self->data_ = tmp;
		self->head_ = self->data_;
		self->capacity_ = newCap;
	}

	int headPos = (((char*) self->head_) - ((char*) self->data_))/self->elemSize_;	
	if (pos < self->size_/2)
	{
		// move o head_ para esquerda uma posicao
		int prevPos;
		if (headPos == 0)
			 prevPos = self->capacity_ - 1;
		else prevPos = headPos - 1;
		self->head_ = ((char*) self->data_) + prevPos * self->elemSize_;
		// copia os elementos a partir de pos para uma posicao a esquerda
		for(int i = 0; i < pos; ++i)
			memmove(c11lAt(self, i), c11lAt(self, i+1), self->elemSize_);
	}
	else
	{
		for(int i = self->size_-1; i >= pos; --i)
			memmove(c11lAt(self, i+1), c11lAt(self, i), self->elemSize_);
	}

	++self->size_;

	puts("c11lInsert: tudo ok!");
	return c11lAt(self, pos);
}

void c11lErase(c11List* self, int pos)
{
	if (pos < self->size_ / 2)
	{
		for (int i = pos; i >= 0; --i)
			memmove(c11lAt(self, i), c11lAt(self, i+1), self->elemSize_);
		self->head_ = c11lAt(self, 1);
	}
	else
	{
		for(int i = pos; i < self->size_-1; ++i)
			memmove(c11lAt(self, i), c11lAt(self, i+1), self->elemSize_);
	}

	--self->size_;
	if (c11lEmpty(self))
	{
		self->head_ = self->data_;
	}
}

void* c11lPushFront(c11List* self)
{
	return c11lInsert(self, 0);
}

void* c11lPushBack(c11List* self)
{
	return c11lInsert(self, self->size_);
}

void c11lPopFront(c11List* self)
{
	c11lErase(self, 0);
}

void c11lPopBack(c11List* self)
{
	c11lErase(self, self->size_-1);
}