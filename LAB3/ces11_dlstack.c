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

/**
    @brief Representa um no da pilha.
    @field data_ Dados armazenados no no.
    @field next_ Proximo no da pilha.
*/
typedef struct Node
{
    void* data_;
    struct Node* next_;
} Node;

/**
    @brief Representa uma pilha encadeada.
    @field first_ Primeiro no da pilha.
    @field last_ Ultimo no da pilha.
    @field size_ Quantidade de elementos.
    @field elemSize_ Tamanho de cada elemento em bytes.
*/
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

/**
    @brief Cria um no contendo uma cópia dos dados fornecidos.
    @param p Dados a serem armazenados.
    @param elemSize Tamanho dos dados em bytes.
    @return Ponteiro para o no criado.
*/
static Node* createNode(void* p, int elemSize)
{
    assert(p  && elemSize > 0);
    Node* node = safeMalloc(sizeof(Node));
    node->data_ = safeMalloc(elemSize);
    memcpy(node->data_, p, elemSize);
    node->next_ = NULL;
    return node;   
}
/**
    @brief Libera um no e seus dados.
    @param node No a ser destruído.
*/
static void destroyNode(Node* node)
{
    if(node)
        free(node->data_);
    free(node);
}

// static Node* getNext(Node* node)
// {
//     return node->next_;
// }

/**
    @brief Retorna os dados armazenados em um nó.
    @param node Nó a ser consultado.
    @return Ponteiro para os dados do nó.
*/
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
    if (c11sEmpty(self))
        return NULL;
    return getData(self->first_);
}

void c11sPush(c11Stack* self, void* p)
{
    Node* newNode = createNode(p, self->elemSize_);
    newNode->next_ = self->first_;
    self->first_ = newNode;
    if (!self->last_)
        self->last_ = newNode;

    ++self->size_;
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