// Arquivo: main.c
//
// [CES-11] T30.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "ces11_pqueue.h"
#include "tarefa.h"

#define LINE_SIZE 80

// variavel global para imprimir o cabecalho 
bool primeiroComandoProxima = true;

void agendaTerminar(c11pqueue *agenda, FILE* saida)
{
	fprintf(saida, "\n");
	fprintf(saida, "--------------------------------------------------\n");
	fprintf(saida, "FICA PARA O DIA SEGUINTE                          \n");
	fprintf(saida, "--------------------------------------------------\n");

	if (c11pqEmpty(agenda))
	{
		fprintf(saida, "Agenda vazia.\n");
	}

	while (!c11pqEmpty(agenda))
	{
		tarefaPrint(c11pqTop(agenda), saida);
		c11pqPop(agenda);
	}
}

void agendaRemover(c11pqueue *agenda, FILE* saida)
{
	if (primeiroComandoProxima)
	{
		primeiroComandoProxima = false;
		fprintf(saida, "--------------------------------------------------\n");
		fprintf(saida, "RESPOSTAS DAS CONSULTAS                           \n");
		fprintf(saida, "--------------------------------------------------\n");
	}
	if (c11pqEmpty(agenda))
	{
		fprintf(saida, "AVISO Nao ha tarefas na agenda\n");
	}
	else
	{
		tarefaPrint(c11pqTop(agenda), saida);
		c11pqPop(agenda);
	}
}

void agendaAdicionar(c11pqueue* agenda, char* buffer)
{
	char comando[20];
	char descricao[50];
	int prioridade;
	// Pega a prioridade
	sscanf(buffer,"%s %d", comando, &prioridade);
	// Pega a descricao
	char *	p = buffer+strlen(comando);
	while(isspace(*p) || isdigit(*(p)))
		p++;
	strcpy(descricao, p);

	// cria a tarefa e coloca na agenda
	tarefa* t = tarefaInit(prioridade, descricao);
	c11pqPush(agenda, t, tarefaCompara);
	// tarefaInit usa malloc, c11pqPush copia, entao precisa dar free:
	tarefaFree(t);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s [path]", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// Abrir arquivos
	FILE *entrada = fopen(argv[1], "r");
	if (!entrada)
	{
		fprintf(stderr, "erro: arquivo '%s' nao encontrado.\n", argv[1]);
		exit(EXIT_FAILURE);
	} 
	
	FILE *saida = fopen("saida.txt", "w");
	if (!entrada)
	{
		fprintf(stderr, "erro: nao foi possivel criar arquivo de saida.\n");
		exit(EXIT_FAILURE);
	}

	// Cabecalho do arquivo de saida
	fprintf(saida, "CABECALHO\nSugou de escrever :/\n\n\n\n");

	// Inicializar agenda
	c11pqueue* agenda = c11pqInit(sizeof(tarefa));
	puts("Inicializado.");
	
	// Ler arquivo de entrada e processar
	char buffer[LINE_SIZE];
	while(fgets(buffer, LINE_SIZE, entrada) != NULL)
	{
		char c;
		sscanf(buffer, " %c", &c);
		
		char comando[20];

		if (c != '#')
		{	
			// Ler comando
			sscanf(buffer,"%s", comando);
			
			if (strcmp(comando, "FIM") == 0)
				agendaTerminar(agenda, saida);
			else if (strcmp(comando, "PROXIMA") == 0)
				agendaRemover(agenda, saida);
			else if (strcmp(comando, "NOVA") == 0)
				agendaAdicionar(agenda, buffer);
		}		
	}
	
	// Terminar 
	c11pqFree(agenda);
	fclose(entrada);
	fclose(saida);

	return EXIT_SUCCESS;
}
