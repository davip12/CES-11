// Arquivo: main.c
//
// [CES-11] T30.3: Lab01.I
// Davi Honorio de Brito Pontes
// 9389

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ces11_vector.h"

// Identifica p, n e k no array de parametros.
// tentando aumentar a clareza do meu jeito 'convoluted'
enum Params {P, N, K};

typedef enum {LEFT, RIGHT} Direction;
/**
 *  \brief Rotaciona o vetor v para a direita ou esquerda k posicoes,
 *  de acordo com o modo m.
 *  
 *  \param [in] v vetor a ser rotacionado
 *  \param [in] d determina o 'sentido', esquerda ou direita
 *  \param [in] k numero de posicoes a rotacionar
 */
void rotate(c11vector* v, int elemSize, Direction d, int k)
{
	switch(d)
	{
		void *elem1, *elem2;
		case LEFT:
			while(k-- > 0)
			{
				
				 /**
				  *  depois de 3h, aprendi da pior forma que a ordem da valoração das expressões dos argumentos
				  *  de funcoes em C padrão não é definida. :((
				  *  
				  *  (por isso as variaveis auxiliares sao necessarias)
				  */
				elem1 = c11vPushBack(v);
				elem2 = c11vAt(v, 0);
				
				memcpy(elem1, elem2 , elemSize);
				c11vPopFront(v);
			}
			break;
		case RIGHT:
			while (k-- > 0)
			{
				/**
				 * Não cometerei o mesmo erro de novo...
				 */
				elem1 = c11vInsert(v, 0);
				elem2 = c11vAt(v, c11vSize(v)-1);
				memcpy(elem1, elem2, elemSize);
				c11vPopBack(v);
			}
			break;
		default:
			fprintf(stderr,"rotate: invalid mode.\n");
	}
}

/**
 *  \brief Testa se n eh primo.
 *  
 *  \param [in] n numero a ser testado
 *  \return Retorna verdadeiro se n eh primo, falso, caso contrario.
 *  
 *  \details Ineficiente (testa ate n-1 e nao floor(sqrt(n))).
 */
bool isPrime(int n)
{
	if (n < 2)
		return false;
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return false;
	
	return true;
}

// Macro para preencher o vetor de 0 a n
#define POPULATE(vector, type, n) \
	for (int i = 0; i < n; i++) \
		*((type *) c11vPushBack(vector)) = (type) i;

/**
 *  \brief Executa tarefas de rotacionar ou 'peneirar' um 
 *  vetor (TAD) generico de tamanho n 
 *  de acordo com os parametros p e k.
 */
int main(int argc, char** argv)
{
	if (argc < 4)
	{
		// p = tipo; n = tamanho do vetor; k = posicoes a rotacionar
		fprintf(stderr, "usage: %s <p> <n> <k>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// um jeito 'convoluted' de pegar os argumentos p, n e k de argv
	// preguica de trocar, agr que eu percebi. Mas acho que ta de boah
	int params[3];
	for (int i = 0; i < 3; i++)
		sscanf(argv[i+1], "%d", params+i);
	
	c11vector *vetor, *aux;
	
	int n = params[N];
	
	switch (params[P])
	{
		case 0:
			vetor = c11vInit(sizeof(float), n);
			// 'Popula'
			POPULATE(vetor, float, n);
			// Rotaciona
			rotate(vetor, sizeof(float), LEFT, params[K]);
			// Imprime
			for (int i = 0; i < c11vSize(vetor); i++)
			{
				printf("%.1f",*((float*) c11vAt(vetor, i)));
				if (i != c11vSize(vetor) -1) putchar(' ');
			}
			break;
		case 1:
			vetor = c11vInit(sizeof(double), n);
			// 'Popula'
			POPULATE(vetor, double, n);
			// Rotaciona
			rotate(vetor, sizeof(double), RIGHT, params[K]);
			// Imprime
			for (int i = 0; i < c11vSize(vetor); i++)
			{
				printf("%.1f", *((double*) c11vAt(vetor, i)));
				if (i != c11vSize(vetor) -1) putchar(' ');
			}
			break;
		case 2:
			vetor = c11vInit(sizeof(int), n);
			// 'Popula'
			POPULATE(vetor, int, n);
			// Peneira
			aux = c11vInit(sizeof(int), n);
			for (int i = 0; i < n; i++)
			{
				int val = *((int *) c11vAt(vetor, i));
				if (isPrime(val))
					*((int *) c11vPushBack(aux)) = (int) val;
			}
			// Imprime
			for (int i = 0; i < c11vSize(aux); i++)
			{
				printf("%d",*((int*) c11vAt(aux, i)));
				if (i != c11vSize(aux)-1) putchar(' ');
			}
			break;
		default:
			fprintf(stderr, "main: invalid value of p.\n");
			exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}