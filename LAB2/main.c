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

	tarefas[0] = tarefaInit("primeira tarefa", 10);
	c11pqPush(pq, tarefas[0], compara);
	tarefas[1] = tarefaInit("segunda tarefa", 20);
	c11pqPush(pq, tarefas[1], compara);
	tarefas[2] = tarefaInit("terceira tarefa", 30);
	c11pqPush(pq, tarefas[2], compara);
	tarefas[3] = tarefaInit("essa tarefa veio primeiro", 25);
	c11pqPush(pq, tarefas[3], compara);
	tarefas[4] = tarefaInit("essa tarefa veio depois", 25);
	c11pqPush(pq, tarefas[4], compara);
	tarefas[5] = tarefaInit("essa tarefa veio muito depois", 25);
	c11pqPush(pq, tarefas[5], compara);
	tarefas[6] = tarefaInit("essa veio por ultimo", 5);
	c11pqPush(pq, tarefas[6], compara);
	
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
