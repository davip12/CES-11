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
# define MAXSIZE 32

// struct que representa um item em que o NPC MONSTER carrega
struct Item 
{
	enum ItemType type_ ; // tipo do item {WEAPON, TREASURE}
	char name_ [MAXSIZE]; // nome do item
	int value_;			  // valor do item (se TREASURE; senao -1) pago pelo NPC MERCHANT
	int durability_;	  // # de vezes que pode ser usado (se WEAPON ; senao -1)
};

// struct que representa um NPC
struct NPC
{
	enum NpcType type_;		// tipo do NPC {MONSTER, VILLAGER, MERCHANT}
	char name_ [MAXSIZE]; 	// nome do NPC
	int hp_; 				// pontos de vida do NPC (se MONSTER; senao , -1)
	float tradeRate_; 		// multiplicador usado pelo MERCHANT para pagar pelo seu item
	Item loot_;				// item que o NPC carrega (se MONSTER; vazio se MERCHANT)
};

// struct que representa o PC
struct PC
{
	char name_ [MAXSIZE];	// nome do PC (aqui, voce pode escrever qualquer nome)
	int coins_;				// contador para o dinheiro recebido da venda dos itens
	c11Queue *weapons_ ;	// inventario: ptr para fila de struct Item (WEAPON)
	c11Stack *backpack_ ;	// mochila: ptr para pilha de struct Item (TREASURE)
};

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

PC* pcInit(char* name)
{
    PC* player = safeMalloc(sizeof(PC));

    strcpy(player->name_, name);
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

int getScore(PC* player)
{
    return player->coins_;
}

NPC* parseNPC(char* buffer)
{
    char mobType[MAXSIZE];
    NPC mob;
    
    strtok(buffer, "{");
    if (sscanf(buffer, "%s %s %d %f",
            mobType, mob.name_, &mob.hp_, &mob.tradeRate_) != 4)
    {
        fprintf(stderr, "parseNPC: could not resolve NPC.\n");
        return NULL;
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
        return NULL;
    }

    if (mob.type_ != MERCHANT)
    {
        char* lootStr = strtok(NULL, "}");
        if (sscanf(lootStr, "%u %s %d %d", 
            &mob.loot_.type_, mob.loot_.name_, &mob.loot_.value_, &mob.loot_.durability_) != 4)
        {
            fprintf(stderr, "parseNPC: could not resolve NPC loot\n");
            return NULL;
        }
    }

    NPC* npc = createNPC(mob.type_, mob.name_, mob.hp_, mob.tradeRate_, mob.loot_);
    return npc;
}

bool processEncounter(PC* player, NPC* mob, FILE* stream)
{
    // flag 
    bool defeated = false;
    // flag para imprimir a mensagem da arma utilizada
    bool changedWeapon = true;
    switch(mob->type_)
    {
        case MONSTER:
        fprintf(stream, "\nCOMBAT!\n");
        fprintf(stream, "Now playing: Battle Theme!\n");
        fprintf(stream, "A wild %s has appeared. \n", mob->name_);
        while(mob->hp_ > 0 && !defeated)
        {
            if (c11qEmpty(player->weapons_))
            {
                fprintf(stream, "You have no more weapons... you're finished!\n\n");
                fprintf(stream, "Defeted by %s.\n", mob->name_);
                defeated = true;
            }
            else
            {
                Item* w = c11qFront(player->weapons_);
                if (changedWeapon)
                {
                    changedWeapon = false;
                    fprintf(stream, "You atack %s with the %s. It's not very effective.\n", mob->name_, w->name_);
                }
                // Atualiza a vida do inimigo e a durabilidade da arma
                --mob->hp_;
                --w->durability_;
                if (w->durability_ == 0)
                {
                    fprintf(stream, "%s has broken! Taking next weapon, if any...\n", w->name_);
                    c11qPop(player->weapons_);
                    w = NULL;
                    changedWeapon = true;
                }
            }
        }
        // 'Looteia'
        if(!defeated)
        {
            fprintf(stream, "\nVICTORY!\n");
            fprintf(stream, "Now playing: Victory Fanfare\n");
            fprintf(stream, "%s is finished. Looting...\n", mob->name_);
            if(mob->loot_.type_ == TREASURE)
            {
                c11sPush(player->backpack_, &mob->loot_);
                fprintf(stream, "You get a %s! It's worth %d coins.\n", 
                    mob->loot_.name_, mob->loot_.value_);
            }
            else
            {
                c11qPush(player->weapons_, &mob->loot_);
                fprintf(stream, "A new weapon! You got the %s (%d durability).\n", 
                    mob->loot_.name_, mob->loot_.durability_);
            } 
        }
        break;
        case VILLAGER:
            fprintf(stream, "\nYou encouter %s. They won't tell you " 
                "their secrets, but motivate you to continue!\n", mob->name_);
        break;
        case MERCHANT:
        fprintf(stream, "\nYou encouter %s. They are willing to buy your treasure.\n", mob->name_);
        if (c11sEmpty(player->backpack_))
        {
            fprintf(stream,"Unfortunately, you don't have any loot. Time to find more monsters!\n");
        }
        else
        {
            fprintf(stream, "You decide is time for a pause.\n");
            fprintf(stream, "Now playing: Shop Theme\n");
        }

        while(!c11sEmpty(player->backpack_))
        {
            Item* l = c11sTop(player->backpack_);
            if (l)
            {
                int salePrice = l->value_ * mob->tradeRate_;
                player->coins_ += salePrice;
                fprintf(stream, "%s sold for %d coins!\n", l->name_, salePrice);
                c11sPop(player->backpack_);
            }
            else
            {
                fprintf(stream, "Your backpack is now empty!\n");
            }
        }
        fprintf(stream, "%s take leave.\n", mob->name_);
        break;
        default:
            fprintf(stream, "\nsomething strange happend, but you can't exactly tell what.\n");
    }

    return defeated;
}