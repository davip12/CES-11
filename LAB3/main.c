// Arquivo: main.c
//
// [CES-11] T30.3: Lab02.I
// Davi Honorio de Brito Pontes
// 9389

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game.h"

#define BUFFER_SIZE 512

#define PC_NAME "Vaan \"Ratsbane\""

/**
*   @brief Executa o programa principal do jogo.
*   @param argc Quantidade de argumentos da linha de comando.
*   @param argv Argumentos da linha de comando.
*   @return EXIT_SUCCESS em caso de execução normal.
*/
int main(int argc, char** argv)
{
	if (argc < 3)
	{
		fprintf(stderr, "usage: %s [path] [path]", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Abrir arquivos
	FILE *entrada = fopen(argv[1], "r");
	if (!entrada)
	{
		fprintf(stderr, "erro: arquivo '%s' nao encontrado.\n", argv[1]);
		exit(EXIT_FAILURE);
	} 
	
	FILE *saida = fopen(argv[2], "w");
	if (!entrada)
	{
		fprintf(stderr, "erro: nao foi possivel criar arquivo de saida.\n");
		exit(EXIT_FAILURE);
	}

	// Buffer para leitura da linha do arquivo
	char buffer[BUFFER_SIZE];
	int line = 0;

	// Inicializa o PC
	PC* player = pcInit(PC_NAME);

	// Inicio do arquivo de saida
	fprintf(saida, "Welcome to First Fantasy! A (non) interactive fiction.\n\n");
	fprintf(saida, "=============================================================\n");
	fprintf(saida, 
		"You are %s, and your dream is to become a Sky Pirate!\n"
		"Will you accumulate enough coins to buy an airship?\n"
		"LET'S BEGIN!\n", PC_NAME);
	fprintf(saida, "============================================================\n");

	// Flags de Fim de Jogo
	bool badEnding = false;

	// Loop de leitura
	while(!badEnding && fgets(buffer, BUFFER_SIZE, entrada) != NULL)
	{
		// Conta as linhas para reportar erros
		line++;
		
		// Le o NPC da linha atual
		NPC* mob = parseNPC(buffer);
		if (!mob)
		{
			fprintf(stderr, "error: could not parse NPC on line %d\n", line);
			continue;
		}
		
		// Processa o encontro
		badEnding = processEncounter(player, mob, saida);

		// Desaloca o NPC
		destroyNPC(mob);
	}

	fprintf(saida, "It's the end of your journey.\n");

	if(badEnding)
	{
		// Se o PC foi derrotado em combate
		fprintf(saida, "\n#### |Game Over| ####");
	}
	else 
	{
		fprintf(saida,
			"\n"
			"=================================================================\n"
			"Despite accumulating some coins, you won't need any of them.\n"
			"You have found somewhere your long lost older brother's chest\n"
			"full of his lifetime savings. You now can buy an airship\n"
			"and fulfill your dreams!\n"
			"Good Ending.\n"
			"=================================================================\n\n");
		fprintf(saida, "#### |The End| Score: %d ####", getScore(player));
	}

	// Termina o programa
	freePC(player);
	fclose(entrada);
	fclose(saida);
	return EXIT_SUCCESS;
}