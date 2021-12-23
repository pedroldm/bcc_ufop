#ifndef listasEncadeadas_h
#define listasEncadeadas_h

typedef struct
{
    int nroInteiro;
} TItem;

typedef struct celula
{
    struct celula *pProx;
    TItem item;
} TCelula;

typedef struct
{
    TCelula *pPrimeiro, *pUltimo;
} TLista;

void concatenarListas(TLista *lista1, TLista *lista2);
void dividirListas(TLista *lista1, TLista *lista2, int i);
void copiarListas(TLista *lista1, TLista *lista2);
int pesquisarElemento(TLista *lista1, int elemento);

#endif