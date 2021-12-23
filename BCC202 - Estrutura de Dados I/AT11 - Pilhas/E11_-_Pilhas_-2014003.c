#include <stdio.h>

typedef struct
{
    int chave;
} TItem;

typedef struct celula
{
    TItem item;
    struct celula *pProx;
} TCelula;

typedef struct
{
    TCelula *cabeca;
} TPilha;

void TPilha_Inicia(TPilha *Pilha)
{
    Pilha->cabeca = (TCelula *)malloc(sizeof(TCelula));
    Pilha->cabeca->pProx = NULL;
}

int TPilha_EhVazia(TPilha *Pilha)
{
    return (Pilha->cabeca->pProx == NULL);
}

void TPilha_Push(TPilha *Pilha, TItem inserir)
{
    TCelula *pAux = (TCelula *)malloc(sizeof(TCelula));
    pAux->item = inserir;
    pAux->pProx = Pilha->cabeca->pProx;
    Pilha->cabeca->pProx = pAux;
}

void TPilha_Pop(TPilha *Pilha)
{
    TCelula *pAux = Pilha->cabeca->pProx;
    Pilha->cabeca->pProx = pAux->pProx;
    free(pAux);
}

void TPilha_Libera(TPilha *Pilha)
{
    TCelula *pAux = Pilha->cabeca->pProx, *pAux2;

    while (pAux != NULL)
    {
        pAux2 = pAux;
        pAux = pAux->pProx;
        free(pAux2);
    }
}