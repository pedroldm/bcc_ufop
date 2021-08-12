#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>

int *alocaVetor(int *vetor, int n)
{
    vetor = (int *)malloc(n * sizeof(int));
    if (vetor == NULL)
    {
        printf("Memória insuficiente.\n");
        exit(1);
    }

    return vetor;
}

int *desalocaVetor(int *vetor)
{
    free(vetor);
    return NULL;
}

void particionarVetor(int *vetor, int margem_Esquerda, int n, int *movimentos)
{
    if (margem_Esquerda < n)
    {
        int nova_Margem = (margem_Esquerda + n) / 2;
        particionarVetor(vetor, margem_Esquerda, nova_Margem, movimentos);
        particionarVetor(vetor, nova_Margem + 1, n, movimentos);
        mergeSort(vetor, margem_Esquerda, nova_Margem, n, movimentos);
    }
}

void mergeSort(int *vetor, int margem_Esquerda, int nova_Margem, int n, int *movimentos)
{
    int tamanho_Esquerda = (nova_Margem - margem_Esquerda + 1), tamanho_Direita = (n - nova_Margem);
    int *vetor_Esquerda = (int *)malloc(tamanho_Esquerda * sizeof(int));
    int *vetor_Direita = (int *)malloc(tamanho_Direita * sizeof(int));
    int i, j;

    for (i = 0; i < tamanho_Esquerda; i++)
    {
        vetor_Esquerda[i] = vetor[i + margem_Esquerda];
    }

    for (j = 0; j < tamanho_Direita; j++)
    {
        vetor_Direita[j] = vetor[nova_Margem + j + 1];
    }

    i = 0, j = 0;

    for (int k = margem_Esquerda; k <= n; k++)
    {
        if (i == tamanho_Esquerda)
        {
            vetor[k] = vetor_Direita[j++];
        }
        else if (j == tamanho_Direita)
        {
            vetor[k] = vetor_Esquerda[i++];
        }
        else if (vetor_Esquerda[i] < vetor_Direita[j])
        {
            vetor[k] = vetor_Esquerda[i++];
        }
        else
        {
            vetor[k] = vetor_Direita[j++];
            *movimentos += (tamanho_Esquerda - i);
        }
    }

    free(vetor_Direita);
    free(vetor_Esquerda);
}