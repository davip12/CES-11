// Arquivo: ces11_dlstack.c
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#include "ces11_dlstack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct Node
{
    void* data_;
    struct Node* next_;
} Node;

struct c11Stack
{
    Node* first_;
    Node* last_;
	int size_;
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

static Node* createNode(void* p, int elemSize)
{
    assert(p  && elemSize > 0);
    Node* node = safeMalloc(sizeof(Node));
    node->data_ = safeMalloc(elemSize);
    memcpy(node->data_, p, elemSize);
    node->next_ = NULL;
    return node;   
}

static void destroyNode(Node* node)
{
    if(node)
        free(node->data_);
    free(node);
}

static Node* getNext(Node* node)
{
    return node->next_;
}

static Node* getData(Node* node)
{
    return node->data_;
}

c11Stack* c11sInit(int n, int elemSize)
{
	assert(n >= 0 && elemSize > 0);
	c11Stack* stack = safeMalloc(sizeof(c11Stack));

	stack->elemSize_ = elemSize;
	stack->size_ = 0;
	
	stack->first_ = NULL;
	stack->last_ = NULL;

	return stack;
}

void c11sFree(c11Stack* self)
{
    assert(self);
	while(!c11sEmpty(self))
    {
        c11sPop(self);
    }
	free(self);
}

bool c11sEmpty(c11Stack* self)
{
	return self->size_ == 0;
}

int c11sSize(c11Stack* self)
{
	return self->size_;
}

void* c11sTop(c11Stack* self)
{
    return getData(self->first_);
}

void c11sPush(c11Stack* self, void* p)
{
    puts("c11sPush chamado!");
    printf("elemSize_ = %d\n", self->elemSize_);
    Node* newNode = createNode(p, self->elemSize_);
    puts("node criado");
    newNode->next_ = self->first_;
    self->first_ = newNode;
    if (!self->last_)
        self->last_ = newNode;

    ++self->size_;

    puts("c11sPush ok");
}

void c11sPop(c11Stack* self)
{
    if (c11sEmpty(self))
        return;

    Node *prevFirst = self->first_;
    self->first_ = self->first_->next_;
    destroyNode(prevFirst);
    
    if (!self->first_)
        self->last_ = NULL;
    --self->size_;
}