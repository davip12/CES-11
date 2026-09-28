// Arquivo: game.h
//
// [CES-11] T30.3: Lab02.I
// Davi Honorio de Brito Pontes
// 9389

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdio.h>

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

/**
*   @brief Cria um item.
*   @param type Tipo do item.
*   @param name Nome do item.
*   @param value Valor do item.
*   @param durability Durabilidade do item.
*   @return Ponteiro para o item criado.
*/
Item* createItem(enum ItemType type, char* name, int value, int durability);

/**
*   @brief Libera um item.
*   @param self Item a ser destruído.
*/
void destroyItem(Item* self);

/**
*   @brief Cria um NPC.
*   @param type Tipo do NPC.
*   @param name Nome do NPC.
*   @param hp Pontos de vida do NPC.
*   @param tradeRate Taxa (multiplicador) de negociacao.
*   @param loot Item carregado pelo NPC.
*   @return Ponteiro para o NPC criado.
*/
NPC* createNPC(enum NpcType type, char* name, int hp, float tradeRate, Item loot);

/**
*   @brief Libera um NPC.
*   @param self NPC a ser destruído.
*/
void destroyNPC(NPC* self);

/**
*   @brief Inicializa o personagem do jogador.
*   @param name Nome do personagem.
*   @return Ponteiro para o personagem criado.
*/
PC* pcInit(char* name);

/**
*   @brief Libera o personagem e seus recursos.
*   @param self Personagem a ser liberado.
*/
void freePC(PC* player);

/**
*   @brief Retorna a pontuacao do personagem.
*   @param player Personagem a ser consultado.
*   @return Quantidade de moedas acumuladas.
*/
int getScore(PC* player);

/**
*   @brief Converte uma linha de texto em um NPC.
*   @param buffer Texto contendo os dados do NPC.
*   @return Ponteiro para o NPC criado ou NULL em caso de erro.
*/
NPC* parseNPC(char* buffer);

/**
*   @brief Processa um encontro entre o jogador e um NPC.
*   @param player Personagem do jogador.
*   @param mob NPC encontrado.
*   @param stream Fluxo de saida das mensagens do encontro.
*   @return true se o jogador for derrotado, false caso contrario.
*/
bool processEncounter(PC* player, NPC* mob, FILE* stream);

#endif // GAME_H