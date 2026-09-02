// Arquivo: main.c
//
// [CES-11] T30.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ces11_pqueue.h"

#define LINE_SIZE 80

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

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s [path]", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	FILE *entrada = fopen(argv[1], "r");
	if (!entrada)
	{
		fprintf(stderr, "erro: arquivo '%s' nao encontrado.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	c11pqueue* pq = c11pqInit(sizeof(tarefa));
	puts("Inicializado.");
	
	char buffer[LINE_SIZE];
	while(fgets(buffer, LINE_SIZE, entrada) != NULL)
	{
		char c;
		sscanf(buffer, " %c", &c)
		
		if (c == '#')
			continue;
		
	}
	
	puts("Freelando...");
	c11pqFree(pq);
	fclose(entrada);
	puts("Saindo...");
	return EXIT_SUCCESS;
}
