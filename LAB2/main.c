// Arquivo: main.c
//
// [CES-11] T30.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

#include "ces11_pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct tarefa
{
	char descricao[50];
	int prioridade;
} tarefa;

int compara(void* tarefa1, void* tarefa2)
{
	assert(tarefa1);
	assert(tarefa2);
	
	tarefa* t1 = tarefa1;
	tarefa* t2 = tarefa2;
	
	return t1->prioridade - t2->prioridade;
}

void printQueue(c11pqueue* pq)
{
	while (!c11pqEmpty(pq))
	{
		tarefa *top = c11pqTop(pq);
		printf("%d\t%s\n", top->prioridade, top->descricao);
		c11pqPop(pq);
	}
}

tarefa* tarefaInit(char *msg, int p)
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

void tarefaErase(tarefa* t)
{
	free(t);
	t = NULL;
}
void tarefaPrint(tarefa* t)
{
	assert(t);
	printf("%d\t%s\n", t->prioridade, t->descricao);
}

int main(void)
{
	puts("Opa, cheguei.");
	c11pqueue* pq = c11pqInit(sizeof(tarefa));
	
	puts("Inicializado.");
	tarefa* tarefas[10];
	
	for (int i = 0; i < 7; i++)
	{
		char msg[50];
		sprintf(msg, "Tarefa %d", i);
		tarefas[i] = tarefaInit(msg, 7-i);
		c11pqPush(pq, tarefas[i], compara);
	}

	puts("Prontinho! imprimindo...");
	
	printQueue(pq);
	puts("Freelando...");
	for (int i = 0; i < 7; i++)
	{
		tarefaErase(tarefas[i]);
	}
	c11pqFree(pq);
	puts("Saindo...");
	return 0;
}
