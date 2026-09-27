// Arquivo: main.c
//
// [CES-11] T30.3: Lab01.II
// Davi Honorio de Brito Pontes
// 9389

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "ces11_pqueue.h"
#include "tarefa.h"

#define LINE_SIZE 80 // tamanho maximo da linha da entrada

// Prototipos

// agendaTerminar: imprime as tarefas que nao foram 
// retiradas da agenda e ficaram na memoria. 
void agendaTerminar(c11pqueue *agenda, FILE* saida);

// agendaRemover: retira uma tarefa da agenda apos a 
// a chamada do usuario (suponhe-se que ela foi realizada)
void agendaRemover(c11pqueue *agenda, FILE* saida);

// agendaAdicionar: adiciona uma tarefa na agenda
void agendaAdicionar(c11pqueue* agenda, char* buffer);

// terminarPrograma: fecha os arquivos, libera a mememoria e sai. 
void terminarPrograma(c11pqueue* agenda, FILE* entrada, FILE* saida);

// main: Le o arquivo de entrada e atualiza uma agenda eletronica a partir
// de comandos, como 'NOVA' e 'PROXIMA', ou termina, com 'FIM'. 
// Organiza tarefas de acordo com a prioridade especificada. 
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
	fprintf(saida, "--------------------------------------------------\n");
	fprintf(saida, "	Agenda Eletronica - Arquivo de Saida          \n");
	fprintf(saida, "--------------------------------------------------\n");
	fprintf(saida, "             Paves 2026 | davipontes54@gmail.com  \n");
	fprintf(saida, "          CES-11 | Prof. Guilherme \"GOAT\" Chagas\n");

	fprintf(saida, "--------------------------------------------------\n");
	fprintf(saida, "RESPOSTAS DAS CONSULTAS                           \n");
	fprintf(saida, "--------------------------------------------------\n");
	
	// Inicializar agenda
	c11pqueue* agenda = c11pqInit(sizeof(tarefa));
	
	// Ler arquivo de entrada e processar
	char buffer[LINE_SIZE];
	while(fgets(buffer, LINE_SIZE, entrada) != NULL)
	{
		// Testa se o primeiro caracter da linha e' '#'
		char c;
		sscanf(buffer, " %c", &c);
		
		char comando[20];
		if (c != '#')
		{	
			// Ler comando
			sscanf(buffer,"%s", comando);
			// Executar
			if (strcmp(comando, "FIM") == 0)
			{
				agendaTerminar(agenda, saida);
				terminarPrograma(agenda, entrada, saida);
			}
			else if (strcmp(comando, "PROXIMA") == 0)
				agendaRemover(agenda, saida);
			else if (strcmp(comando, "NOVA") == 0)
				agendaAdicionar(agenda, buffer);
		}		
	}
	
	// Terminar 
	terminarPrograma(agenda, entrada, saida);
	return EXIT_SUCCESS;
}

// Implementacoes

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

void terminarPrograma(c11pqueue* agenda, FILE* entrada, FILE* saida)
{
	c11pqFree(agenda);
	fclose(entrada);
	fclose(saida);

	exit(EXIT_SUCCESS);
}

