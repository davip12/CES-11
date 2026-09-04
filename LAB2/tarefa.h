// Arquivo: tarefa.h
//
// [CES-11] T30.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

#ifndef TAREFA_H
#define TAREFA_H

#include <stdio.h>

typedef struct tarefa
{
	char descricao[50];
	int prioridade;
} tarefa;

int tarefaCompara(void* tarefa1, void* tarefa2);

tarefa* tarefaInit(int p, char *msg);

void tarefaFree(tarefa* t);

void tarefaPrint(tarefa* t, FILE* saida);

#endif // TAREFA_H