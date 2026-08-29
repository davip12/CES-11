// Arquivo : ces11_pqueue.h
//
// [CES-11] T3.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

#ifndef CES11_PQUEUE_H
#define CES11_PQUEUE_H

typedef struct c11vector c11pqueue;

/*
 * @brief Inicializa uma fila generica, capaz de armazenar elementos de tamanho
   elemSize.
 * @param [int] elemSize: tamanho, em bytes, de cada elemento
 * a ser armazenado na fila de prioridades.
 * @return [c11pqueue*]: ponteiro para a fila de prioridades recem-criada.
 */
c11pqueue* c11pqInit(int elemSize);

/*
 * @brief Libera toda a memoria alocada para a fila de prioridades.
 * @param [c11pqueue *self]: fila a ser liberado (desalocado).
 */
void c11pqFree(c11pqueue *self);

/*
 * @brief Verifica se a fila possui elementos.
 * @param [c11pqueue *self]: fila de prioridades a ser verificada.
 * @return [bool]: verdadeiro se o vetor esta’ vazio, falso caso contrario.
 */
bool c11pqEmpty(c11pqueue *self);

/*
 * @brief Retorna o numero de elementos atualmente armazenados na fila.
 * @param [c11pqueue *self]: fila a ser verificada.
 * @return [int]: quantidade de elementos no vetor.
 */
int c11pqSize(c11pqueue *self);

/*
 * @brief Funcao que insere o elemento passado na posicao correta na fila de acordo
 * com a prioridade (faz busca binaria para encontrar a posicao correta).
 * @param [c11pqueue *self]: fila de prioridades no qual o elemento sera inserido.
 * @param [void*]: ponteiro para a o item que sera’ armazenado na fila.
 * @param int (*compara )(void*, void*): ponteiro para funcao que compara dois itens.
 */
void c11pqPush(c11pqueue *self, void *q, int (*compare)(void*, void*));

/*
 * @brief Remove o item da fila de prioridades com a maior prioridade.
 * Note que nossa fila de prioridades vai remover os itens da ultima
 * posicao do vetor. Com isso, basta fazermos popBack no vetor.
 * @param [c11pqueue *self]: fila de prioridades em que o primeiro
 * elemento sera removido.
 */
void c11pqPop(c11pqueue *self);

/*
 * @brief Retornar o primeiro elemento da fila de prioridades (ultimo elemento do
 * c11vector: funcao back).
 * @param [c11pqueue *self]: .
 * @return [void*]: .
 */
void* c11pqTop(c11pqueue *self);

#endif // CES11_PQUEUE_H