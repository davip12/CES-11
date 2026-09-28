// Arquivo: game.h
//
// [CES-11] T30.3: Lab02.I
// Davi Honorio de Brito Pontes
// 9389

#ifndef GAME_H
#define GAME_H

#include "ces11_ccqueue.h"
#include "ces11_dlstack.h"

// tipo de NPC (usado na struct NPC)
enum NpcType {MONSTER, MERCHANT, VILLAGER};
// tipo de item (usado na struct Item)
enum ItemType {WEAPON, TREASURE};

// struct que representa um item em que o NPC MONSTER carrega
typedef struct Item Item;

// struct que representa um NPC
typedef struct NPC NPC;

// struct que representa o PC
typedef struct PC PC;

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


Item* createItem(enum ItemType type, char* name, int value, int durability);
void destroyItem(Item* self);

PC* pcInit();
void freePC(PC* player);


#endif // GAME_H