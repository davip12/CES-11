// Arquivo: tarefa.c
//
// [CES-11] T30.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

#include "tarefa.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int tarefaCompara(void* tarefa1, void* tarefa2)
{
	assert(tarefa1 && tarefa2);
	
	tarefa* t1 = tarefa1;
	tarefa* t2 = tarefa2;
	
	return t1->prioridade - t2->prioridade;
}

tarefa* tarefaInit(int p, char *msg)
{
	assert(strlen(msg) < 50);
	
	void* tmp = malloc(sizeof(tarefa));
	assert(tmp);
	
	if (!tmp)
		return NULL;
	tarefa* t = tmp;
	
	strcpy(t->descricao, msg);
	t->prioridade = p;
	return t;
}

void tarefaFree(tarefa* t)
{
	free(t);
	t = NULL;
}

void tarefaPrint(tarefa* t, FILE* saida)
{
	fprintf(saida, "%2d       %s", t->prioridade, t->descricao);
}
