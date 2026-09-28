// Arquivo: ces11_dlstack.h
//
// [CES-11] T30.3: Lab02
// Davi Honorio de Brito Pontes
// 9389

#ifndef CES11_DLSTACK_H
#define CES11_DLSTACK_H

/**
*   @brief Representa uma pilha encadeada.
*/
typedef struct c11Stack c11Stack;

/**
*   @brief Inicializa uma pilha.
*   @param n Capacidade inicial da pilha.
*   @param elemSize Tamanho, em bytes, de cada elemento.
*   @return Ponteiro para a pilha criada.
*/
c11Stack* c11sInit(int n, int elemSize);

/**
*   @brief Libera a memoria ocupada pela pilha.
*   @param self Pilha a ser liberada.
*/
void c11sFree(c11Stack* self);

/**
*   @brief Verifica se a pilha esta' vazia.
*   @param self Pilha a ser consultada.
*   @return true se estiver vazia, false caso contrário.
*/
bool c11sEmpty(c11Stack* self);

/**
*   @brief Retorna a quantidade de elementos da pilha.
*   @param self Pilha a ser consultada.
*   @return Numero de elementos.
*/
int c11sSize(c11Stack* self);

/**
*   @brief Retorna o elemento no topo da pilha.
*   @param self Pilha a ser consultada.
*   @return Ponteiro para o elemento do topo ou NULL se vazia.
*/
void* c11sTop(c11Stack* self);

/**
*   @brief Insere um elemento no topo da pilha.
*   @param self Pilha onde o elemento sera' inserido.
*   @param p Elemento a ser armazenado.
*/
void c11sPush(c11Stack* self, void* p);

/**
*   @brief Remove o elemento do topo da pilha.
*   @param self Pilha da qual o elemento sera' removido.
*/
void c11sPop(c11Stack* self);

#endif // CES11_STACK_H