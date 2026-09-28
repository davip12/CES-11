// Arquivo: ces11_ccqueue.h
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#ifndef CES11_CCQUEUE_H
#define CES11_CCQUEUE_H

#include <stdbool.h>

typedef struct c11List c11Queue;

/** 
    @brief Inicializa uma fila de elementos.
    @param n Capacidade inicial da fila.
    @param elemSize Tamanho, em bytes, de cada elemento.
    @return Ponteiro para a fila criada.
*/
c11Queue* c11qInit(int n, int elemSize);

/**
    @brief Libera a memória ocupada pela fila.
    @param self Fila a ser liberada.
*/
void c11qFree(c11Queue* self);

/**
    @brief Retorna o numero de elementos da fila.
    @param self Fila a ser consultada.
    @return Quantidade de elementos.
*/
int c11qSize(c11Queue* self);

/**
    @brief Verifica se a fila esta' vazia.
    @param self Fila a ser consultada.
    @return true se estiver vazia, false caso contrario.
*/
bool c11qEmpty(c11Queue* self);

/**
    @brief Retorna o primeiro elemento da fila.
    @param self Fila a ser consultada.
    @return Ponteiro para o primeiro elemento.
*/
void* c11qFront(c11Queue* self);

/**
    @brief Insere um elemento no final da fila.
    @param self Fila onde o elemento será inserido.
    @param p Elemento a ser copiado para a fila.
*/
void c11qPush(c11Queue* self, void* p);

/**
    @brief Remove o primeiro elemento da fila.
    @param self Fila da qual o elemento sera' removido.
*/
void c11qPop(c11Queue* self);

#endif // CES11_CCQUEUE_H