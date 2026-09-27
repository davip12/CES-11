// Arquivo: tarefa.h
//
// [CES-11] T30.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

// TAD de tarefa 

#ifndef TAREFA_H
#define TAREFA_H

#include <stdio.h>

typedef struct tarefa
{
	char descricao[50];
	int prioridade;
} tarefa;

/*
 * @brief Compara as prioridades de duas tarefas.
 * @param [void *tarefa1]: primeira tarefa a ser comparada.
 * @param [void *tarefa2]: segundatarefa a ser comparada.
 * @return [int]: prioridade da primeira subtraida da segunda.
 */
int tarefaCompara(void* tarefa1, void* tarefa2);


/*
 * @brief Aloca memoria para uma tarefa e a preenche.
 * @param [int] p: prioridade da tarefa.
 * @param [char *msg]: descricao da tarefa.
 * @return [tarefa*]: ponteiro para a terefa alocada.
 */
tarefa* tarefaInit(int p, char *msg);

/*
 * @brief Libera a memoria alocada para a tarefa
 * @param [tarefa* t]: tarefa a ser desalocada.
 */
void tarefaFree(tarefa* t);

/*
 * @brief Imprime o conteudo de uma tarefa no arquivo de saida. 
 * @param [tarefa* t]: tarefa a ser impressa.
 * @param [FILE* saida]: arquivo de saida.
 */
void tarefaPrint(tarefa* t, FILE* saida);

#endif // TAREFA_H