// Arquivo: ces11_list.h
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#ifndef CES11_LIST_H
#define CES11_LIST_H

#include <stdbool.h>

/**
    @brief Representa uma lista circular contigua.
*/
typedef struct c11List c11List;

/**
    @brief Inicializa uma lista.
    @param n Capacidade inicial da lista.
    @param elemSize Tamanho, em bytes, de cada elemento.
    @return Ponteiro para a lista criada.
*/
c11List* c11lInit(int n, int elemSize);

/**
    @brief Libera a memoria ocupada pela lista.
    @param self Lista a ser liberada.
*/
void c11lFree(c11List* self);

/**
    @brief Retorna a quantidade de elementos da lista.
    @param self Lista a ser consultada.
    @return Numero de elementos.
*/
int c11lSize(c11List* self);

/**
    @brief Retorna o tamanho de cada elemento da lista.
    @param self Lista a ser consultada.
    @return Tamanho do elemento em bytes.
*/
int c11lElemSize(c11List* self);

/**
    @brief Verifica se a lista esta' vazia.
    @param self Lista a ser consultada.
    @return true se estiver vazia, false caso contrario.
*/
bool c11lEmpty(c11List* self);

/**
    @brief Retorna o elemento na posicao indicada.
    @param self Lista a ser consultada.
    @param pos Posicao do elemento.
    @return Ponteiro para o elemento na posicao indicada.
*/
void* c11lAt(c11List* self, int  pos);

/**
    @brief Retorna o primeiro elemento da lista.
    @param self Lista a ser consultada.
    @return Ponteiro para o primeiro elemento.
*/
void* c11lFront(c11List* self);

/**
    @brief Retorna o ultimo elemento da lista.
    @param self Lista a ser consultada.
    @return Ponteiro para o ultimo elemento.
*/
void* c11lBack(c11List* self);

/**
    @brief Insere uma posicao na lista.
    @param self Lista onde sera' feita a insercao.
    @param pos Posicao onde o novo elemento será inserido.
    @return Ponteiro para a posicao inserida.
*/
void* c11lInsert(c11List* self, int pos);

/**
    @brief Remove um elemento da lista.
    @param self Lista da qual o elemento sera' removido.
    @param pos Posicao do elemento a ser removido.
*/
void c11lErase(c11List* self, int pos);

/**
    @brief Insere um elemento no início da lista.
    @param self Lista onde sera' feita a insercao.
    @return Ponteiro para a posicao inserida.
*/
void* c11lPushFront(c11List* self);

/**
    @brief Insere um elemento no final da lista.
    @param self Lista onde sera' feita a insercao.
    @return Ponteiro para a posicao inserida.
*/
void* c11lPushBack(c11List* self);

/**
    @brief Remove o primeiro elemento da lista.
    @param self Lista da qual o elemento sera' removido.
*/
void c11lPopFront(c11List* self);

/**
    @brief Remove o ultimo elemento da lista.
    @param self Lista da qual o elemento sera' removido.
*/
void c11lPopBack(c11List* self);

#endif // LIST_H
