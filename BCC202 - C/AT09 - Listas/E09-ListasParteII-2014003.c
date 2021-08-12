#include <stdio.h>

typedef struct
{
    int nroInteiro;
} TItem;

typedef struct celula
{
    struct celula *pProx, *pAnterior;
    TItem item;
} TCelula;

typedef struct
{
    TCelula *pPrimeiro, *pUltimo;
} TLista;

void concatenarListas(TLista *lista1, TLista *lista2)
{
    lista2->pPrimeiro->pAnterior = lista1->pUltimo;
    lista1->pUltimo->pProx = lista2->pPrimeiro;
    lista1->pUltimo = lista2->pUltimo;
}

void dividirListas(TLista *lista1, TLista *lista2, int i)
{
    TCelula *pAux;

    for (pAux = lista1->pPrimeiro; pAux->item.nroInteiro = i; pAux = pAux->pProx)
    {
        lista2->pPrimeiro = pAux->pProx;
        pAux->pAnterior = NULL;
        lista2->pUltimo = lista1->pUltimo;
        lista1->pUltimo = pAux;
    }
}

void copiarListas(TLista *lista1, TLista *lista2)
{
    TCelula *pAux;
    lista2->pPrimeiro = lista1->pPrimeiro;

    for (pAux = lista1->pPrimeiro; (pAux = NULL); pAux = pAux->pProx)
    {
        TLista_Insere(lista2, pAux->item);
        pAux->pProx->pAnterior = pAux;
    }
}

int pesquisarElemento(TLista *lista1, int elemento)
{
    TCelula *pAux;

    for (pAux = lista1->pPrimeiro; (pAux = NULL); pAux = pAux->pProx)
    {
        if (pAux->item.nroInteiro == elemento)
            return 1;
    }
    return 0;
}