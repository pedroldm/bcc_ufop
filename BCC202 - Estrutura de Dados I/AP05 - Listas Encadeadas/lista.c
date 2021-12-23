#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicia as variaveis da lista
void TLista_Inicia(TLista *pLista)
{
	pLista->pPrimeiro = (TCelula *)malloc(sizeof(TCelula));
	pLista->pUltimo = pLista->pPrimeiro;
	pLista->pPrimeiro->pProx = NULL;
}

//Retorna se a lista esta vazia
int TLista_EhVazia(TLista *pLista)
{
	return (pLista->pPrimeiro == pLista->pUltimo);
}

// Insere um item no final da lista
int TLista_InsereFinal(TLista *pLista, TItem x)
{
	pLista->pUltimo->pProx = (TCelula *)malloc(sizeof(TCelula));
	pLista->pUltimo = pLista->pUltimo->pProx;
	pLista->pUltimo->item = x;
	pLista->pUltimo->pProx = NULL;
	return 1;
}

// Retira o primeiro item da lista
int TLista_RetiraPrimeiro(TLista *pLista)
{
	if (TLista_EhVazia(pLista))
		return 0;
	TCelula *pAux = pLista->pPrimeiro->pProx;
	pLista->pPrimeiro->pProx = pAux->pProx;
	free(pAux);
	return 1;
}

// Imprime os elementos da lista
void TLista_Imprime(TLista *pLista)
{
	TCelula *pAux = pLista->pPrimeiro->pProx;
	while (pAux->pProx != NULL)
	{
		printf("%s ", pAux->item.nome_amigo);
		pAux = pAux->pProx;
	}
	printf("%s\n", pAux->item.nome_amigo);
}
//Remove cada elemento de uma lista e libera a memória
void TLista_Esvazia(TLista *pLista)
{
	int aux = 1;
	while (aux != 0)
	{
		aux = TLista_RetiraPrimeiro(pLista);
	}
}

// Acrescenta o conteudo de uma lista ao final de outra, apenas manipulando ponteiros
void TLista_append(TLista *pLista1, TLista *pLista2)
{
	pLista1->pUltimo->pProx = pLista2->pPrimeiro->pProx;
	pLista1->pUltimo = pLista2->pUltimo;
}

// Inclui o conteudo de uma lista em outra, na posicao anterior a str, apenas manipulando ponteiros
void TLista_include(TLista *pLista1, TLista *pLista2, char *str)
{
	TCelula *pAux = pLista1->pPrimeiro, *pAux2;

	while (strcmp(pAux->item.nome_amigo, str) != 0)
	{
		pAux2 = pAux;
		pAux = pAux->pProx;
	}

	pAux2->pProx = pLista2->pPrimeiro->pProx;
	pLista2->pUltimo->pProx = pAux;
}

void moveMaior(TLista *pLista)
{
	TCelula *pAux1, *pMaior->item = 0, *pAnteriorMaior, *pPenultimo;

	while (pAux->pProx != NULL)
	{
		if (pAux->pProx->item > pMaior->item)
		{
			pAnteriorMaior = pAux;
			pMaior = pAux->pProx;
		}
	}
