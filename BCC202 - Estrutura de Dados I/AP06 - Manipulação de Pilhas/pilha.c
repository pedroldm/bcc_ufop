#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicia as variaveis da pilha
void Pilha_Inicia(Pilha *pilha)
{
    pilha->cabeca = (Celula *)malloc(sizeof(Celula));
    pilha->cabeca->pProx = NULL;
}

//Retorna se a pilha esta vazia
int Pilha_EhVazia(Pilha *pilha)
{
    return (pilha->cabeca->pProx == NULL);
}

// Insere um item no topo da pilha
int Pilha_Push(Pilha *pilha, Item item)
{
    Celula *pAux = (Celula *)malloc(sizeof(Celula));
    if (pAux == NULL)
    {
        printf("Memória insuficiente.\n");
        return 0;
    }

    pAux->char_expressao = item;
    pAux->pProx = pilha->cabeca->pProx;
    pilha->cabeca->pProx = pAux;

    return 1;
}

// Retira o item do topo da pilha
int Pilha_Pop(Pilha *pilha, Item *item)
{
    Celula *pAux = pilha->cabeca->pProx;
    if (Pilha_EhVazia(pilha))
        return 0;
    pilha->cabeca->pProx = pAux->pProx;
    *item = pAux->char_expressao;
    free(pAux);

    return 1;
}

//Remove cada elemento de uma pilha e libera a memória
void Pilha_Esvazia(Pilha *pilha)
{
    Celula *pAux = pilha->cabeca->pProx, *pAux2;

    while (pAux != NULL)
    {
        pAux2 = pAux;
        pAux = pAux->pProx;
        free(pAux2);
    }

    pilha->cabeca->pProx = NULL;
}