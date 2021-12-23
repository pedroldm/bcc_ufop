#include "prioridade.h"
#include <stdio.h>
#include <stdlib.h>

//Manter como especificado
TipoCaixa *alocaVetor(TipoCaixa *heap, int n)
{
    heap = (TipoCaixa *)malloc(n * sizeof(TipoCaixa));
    if (heap == NULL)
    {
        printf("Memória insuficiente.\n");
        exit(1);
    }

    return heap;
}

//Manter como especificado
TipoCaixa *desalocaVetor(TipoCaixa *heap)
{
    free(heap);
    return NULL;
}

//Manter como especificado
void Heap_Constroi(TipoCaixa *heap, int n)
{
    int esq = (n / 2) - 1;
    while (esq >= 0)
    {
        Heap_Refaz(heap, esq, n - 1);
        esq--;
    }
}

//Manter como especificado
void Heap_Refaz(TipoCaixa *heap, int esq, int dir)
{
    int i = esq;
    int j = i * 2 + 1;
    TipoCaixa aux = heap[i];

    while (j <= dir)
    {
        if (j < dir)
        {
            if (heap[j].somar_Tempo > heap[j + 1].somar_Tempo)
                j++;
            else if (heap[j].somar_Tempo == heap[j + 1].somar_Tempo && heap[j + 1].nro_Identificacao < heap[j].nro_Identificacao)
                j++;
        }
        if (aux.somar_Tempo < heap[j].somar_Tempo)
            break;
        if (aux.somar_Tempo == heap[j].somar_Tempo && aux.nro_Identificacao < heap[j].nro_Identificacao)
            break;
        heap[i] = heap[j];
        i = j;
        j = i * 2 + 1;
    }
    heap[i] = aux;
}