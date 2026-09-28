// Arquivo: main.c
//
// [CES-11] T30.3: Lab02.I
// Davi Honorio de Brito Pontes
// 9389

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "game.h"
#include "ces11_ccqueue.h"
#include "ces11_dlstack.h"

#include <assert.h>

NPC* parseNPC(char* str);

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		fprintf(stderr, "usage: %s [path] [path]", argv[0]);
		exit(EXIT_FAILURE);
	}

	puts("Abrindo arquivo de entrada");
	// Abrir arquivos
	FILE *entrada = fopen(argv[1], "r");
	if (!entrada)
	{
		fprintf(stderr, "erro: arquivo '%s' nao encontrado.\n", argv[1]);
		exit(EXIT_FAILURE);
	} 
	

	puts("Abrindo arquivo de saida");
	FILE *saida = fopen(argv[2], "w");
	if (!entrada)
	{
		fprintf(stderr, "erro: nao foi possivel criar arquivo de saida.\n");
		exit(EXIT_FAILURE);
	}

	char buffer[80];
	int line = 0;


	puts("Inicializando player");
	PC* player = pcInit();

	bool gameOver = false;
	bool badEnding = false;

	puts("Iniciando a leitura do arquivo de entrada");
	while(!gameOver && fgets(buffer, 80, entrada) != NULL)
	{
		line++;
		printf("processando linha %d\n", line);
		char mobType[MAXSIZE];
		NPC mob;
		
		strtok(buffer, "{");
		if (sscanf(buffer, "%s %s %d %f",
				mobType, mob.name_, &mob.hp_, &mob.tradeRate_) != 4)
		{
			fprintf(stderr, "error: could not resolve NPC on line %d\n", line);
			continue; 
		}

		if (strcmp(mobType, "MONSTER") == 0)
			mob.type_ = MONSTER;
		else if (strcmp(mobType, "VILLAGER") == 0)
			mob.type_ = VILLAGER;
		else if (strcmp(mobType, "MERCHANT") == 0)
			mob.type_ = MERCHANT;
		else
		{
			fprintf(stderr, "error: unexpected NPC type '%s'\n", buffer);
			mob.type_ = -1;
		}

		if (mob.type_ != MERCHANT)
		{
			char* lootStr = strtok(NULL, "}");
			if (sscanf(lootStr, "%u %s %d %d", 
				&mob.loot_.type_, mob.loot_.name_, &mob.loot_.value_, &mob.loot_.durability_) != 4)
			{
				fprintf(stderr, "error: could not resolve NPC loot on line %d\n", line);
				continue;
			}
		}

		puts("processando encontro");
		switch(mob.type_)
		{
			case MONSTER:
			puts("Monstro encontrado. procesando combate.");
			// COMBATE!
			// Now playing: Battle Theme
			while(mob.hp_ > 0 && !gameOver)
			{
				if (c11qEmpty(player->weapons_))
					badEnding = gameOver = true;

				Item* w = c11qFront(player->weapons_); 
				--mob.hp_;
				--w->durability_;
				if (w->durability_ == 0)
					c11qPop(player->weapons_);
			}
			puts("fim do combate. looteado...");
			// 'Looteia'
			if(!badEnding)
			{
				// VITORIA!
				// Now playing: 'Victory Fanfare'
				if(mob.loot_.type_ == TREASURE)
				{
					puts("tesouro encontrado. guardando na mochila");
					c11sPush(player->backpack_, &mob.loot_);
				}
				else
				{
					puts("arma encontrado. guardando na mochila");
					c11qPush(player->weapons_, &mob.loot_);
				}
			}
			break;
			case VILLAGER:
				// Skip cutscene? (default = yes)
				continue;
			break;
			case MERCHANT:
			while(!c11sEmpty(player->backpack_))
			{
				Item* l = c11sTop(player->backpack_);
				player->coins_ += l->value_ * mob.tradeRate_;
				c11sPop(player->backpack_);
			}
			break;
			default:

		}
	}

	if(badEnding)
	{
		fprintf(saida, "#### |Game Over| ####");
	}
	else 
	{
		fprintf(saida, "#### |The End| Score: %d ####", player->coins_);
	}

	freePC(player);
	fclose(entrada);
	fclose(saida);
	return EXIT_FAILURE;
}
