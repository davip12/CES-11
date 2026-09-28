// Arquivo: game.c
//
// [CES-11] T30.3: Lab02.I
// Davi Honorio de Brito Pontes
// 9389

#include "ces11_ccqueue.h"
#include "ces11_dlstack.h"

#include "game.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// constante do tamanho maximo do buffer para armazenar o nome do PC , NPC e Item

static void* safeMalloc(int bytes)
{
	void* tmp = malloc(bytes);
	if (!tmp)
	{
		fprintf(stderr, "Falha em alocar memoria\n");
		exit(EXIT_FAILURE);		
	}
	return tmp;
}

Item* createItem(enum ItemType type, char* name, int value, int durability)
{
    Item* item = safeMalloc(sizeof(Item));
    item->type_ = type;
	strcpy(item->name_, name);
    item->value_ = value;
    item->durability_ = durability;

    return item;
}

void destroyItem(Item* self)
{
    free(self);
}

NPC* createNPC(enum NpcType type, char* name, int hp, float tradeRate, Item loot)
{
    NPC* npc = safeMalloc(sizeof(NPC));
    npc->type_ = type;		// tipo do NPC {MONSTER, VILLAGER, MERCHANT}
	strcpy(npc->name_, name); 	// nome do NPC
	npc->hp_ = hp; 				// pontos de vida do NPC (se MONSTER; senao , -1)
	npc->tradeRate_ = tradeRate; 		// multiplicador usado pelo MERCHANT para pagar pelo seu item
	npc->loot_ = loot;

    return npc;
}

void destroyNPC(NPC* self)
{
    free(self);
}

PC* pcInit()
{
    PC* player = safeMalloc(sizeof(PC));

    strcpy(player->name_, "Vaan \"Ratsbane\"");
    player->coins_ = 0;
    
    // Inicializa as armas
    player->weapons_ = c11qInit(1, sizeof(Item));

    Item* weapon = createItem(WEAPON, "StickOfTruth", -1, 2);
    c11qPush(player->weapons_, weapon);
    destroyItem(weapon);

    //Inicializa a mochila
    player->backpack_ = c11sInit(2, sizeof(Item));

    return player;
}

void freePC(PC* self)
{
    if (self)
    {
        c11qFree(self->weapons_);
        c11sFree(self->backpack_);
    }
    free(self);
}