// Arquivo: ces11_vector.h
//
// [CES-11] T30.3: Lab01.I
// Davi Honorio de Brito Pontes
// 9389

#ifndef CES_11_VECTOR_H
#define CES_11_VECTOR_H

#include <stdbool.h>

typedef struct c11vector c11vector;
/**
 *  \brief 	Aloca e incializa um vetor generico, capaz de armazenar 
 *  		elementos de tamanho elemSize, com n elementos iniciais.
 *  \param	[int] elemSize: tamanho, em bytes, de cada elemento
 *  		a ser armazenado no vetor.
 *  \param 	[int] n: tamanho incial do vetor (capacidade inicial).
 *  \return	[c11vector*]: ponteiro para o vetor recem-criado.
 */
c11vector* c11vInit(int elemSize, int n);

/**
 *  \brief	Libera toda a memoria alocada para o vetor.
 *  
 *  \param	[c11vector*] self: vetor a ser liberado (desalocado). 
 */
void c11vFree(c11vector *self);

/**
 *  \brief pega o i-esimo elemento do vetor (como se fosse o operador [])
 *  
 *  \param [c11vector *] self vetor do qual se deseja obter o elemento.
 *  \param [int] i indice (posicao) do elemento desejado, comecando em 0.
 *  \return [void *] ponteiro para o i-elemento do vetor.		
 */
void* c11vAt(c11vector *self, int i);

/**
 *  \brief Verifica se o vetor possui elementos.
 *  
 *  \param [c11vector*] self vetor a ser verificado.
 *  \return [bool] verdadeiro se o vetor esta' vazio, falso caso contrario.
 */
bool c11vEmpty(c11vector* self);

/**
 *  \brief Retorna o numero de elementos atualmente armazenados no vetor
 *  
 *  \param [in] self vetor a ser verificado.
 *  \return [int] quantidade de elementos no vetor
 */
int c11vSize(c11vector* self);

/**
 *  \brief Abre espaco para um elemento na posicao pos do vetor.
 *  
 *  \param [in] self vetor no qual o elemento sera inserido.
 *  \param [in] pos posicao em que o novo elemento deve ser inserido.
 *  \return [void*] ponteiro para o espaco do elemento recem-criado.
 */
void* c11vInsert(c11vector* self, int pos);

/**
 *  \brief Abre espaco para um novo elemento na ultima posicao do vetor e
 *  retorna um ponteiro para esse espaco (para que o chamador escreva 
 *  o valor desejado).
 *  
 *  \param [in] self vetor no qual o elemento sera inserido.
 *  \return [void*] ponteiro para o espaço do elemento recem-criado.
 */
void* c11vPushBack(c11vector* self);

/**
 *  \brief Remove o primeiro elemento do vetor, deslocando os
 *  elementos restantes uma posicao para frente.
 *  
 *  \param [in] self vetor no qual o primeiro elemento sera removido.
 */
void c11vPopFront(c11vector* self);

/**
 *  \brief Remove o ultimo elemento do vetor.
 *  
 *  \param [in] self Vetor do qual o ultimo elemento sera removido.
 */
void c11vPopBack(c11vector* self);


#endif // CES_11_VECTOR_H



