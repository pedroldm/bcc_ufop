#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

medalhas_pais *alocar_Vetor(medalhas_pais *vetor_Paises, int quantidade_Paises)
{
    vetor_Paises = (medalhas_pais *)malloc(quantidade_Paises * sizeof(medalhas_pais));
    if (vetor_Paises == NULL)
    {
        printf("Memória insuficiente.\n");
        exit(1);
    }

    return vetor_Paises;
}

medalhas_pais *desalocar_Vetor(medalhas_pais *vetor_Paises)
{
    free(vetor_Paises);

    return NULL;
}

void ler_Quantidade(int *quantidade_Paises)
{
    scanf("%d", quantidade_Paises);
}

void ler_Medalhas(medalhas_pais *vetor_Paises, int quantidade_Paises)
{
    for (int i = 0; i < quantidade_Paises; i++)
    {
        scanf(" %s", vetor_Paises[i].nome_Pais);
        scanf("%d", &vetor_Paises[i].medalhas_Ouro);
        scanf("%d", &vetor_Paises[i].medalhas_Prata);
        scanf("%d", &vetor_Paises[i].medalhas_Bronze);
    }
}

void selectionSort_Ouro(medalhas_pais *vetor_Paises, int quantidade_Paises)
{
    medalhas_pais TAD_aux;

    for (int i = 0; i < quantidade_Paises; i++)
    {
        for (int j = i + 1; j < quantidade_Paises; j++)
        {
            if (vetor_Paises[i].medalhas_Ouro < vetor_Paises[j].medalhas_Ouro)
            {
                TAD_aux = vetor_Paises[i];
                vetor_Paises[i] = vetor_Paises[j];
                vetor_Paises[j] = TAD_aux;
            }
        }
    }
}

//margem_Esquerda e margem_Direita delimitam o intervalo de valores iguais.
void bubbleSort_Prata(medalhas_pais *vetor_Paises, int quantidade_Paises)
{
    medalhas_pais TAD_aux;

    for (int i = 0; i < quantidade_Paises - 1; i++)
    {
        if (vetor_Paises[i].medalhas_Ouro == vetor_Paises[i + 1].medalhas_Ouro)
        {
            int margem_Esquerda = i;
            int margem_Direita = i + 1;
            while (vetor_Paises[margem_Esquerda].medalhas_Ouro == vetor_Paises[margem_Direita].medalhas_Ouro && margem_Direita < quantidade_Paises)
                margem_Direita++;
            i = margem_Direita - 1;

            for (int j = margem_Esquerda; j < margem_Direita; j++)
            {
                for (int k = margem_Esquerda; k < margem_Direita - 1; k++)
                {
                    if (vetor_Paises[k].medalhas_Prata < vetor_Paises[k + 1].medalhas_Prata)
                    {
                        TAD_aux = vetor_Paises[k];
                        vetor_Paises[k] = vetor_Paises[k + 1];
                        vetor_Paises[k + 1] = TAD_aux;
                    }
                }
            }
        }
    }
}

void bubbleSort_Bronze(medalhas_pais *vetor_Paises, int quantidade_Paises)
{
    medalhas_pais TAD_aux;

    for (int i = 0; i < quantidade_Paises - 1; i++)
    {
        if (vetor_Paises[i].medalhas_Ouro == vetor_Paises[i + 1].medalhas_Ouro && vetor_Paises[i].medalhas_Prata == vetor_Paises[i + 1].medalhas_Prata)
        {
            int margem_Esquerda = i;
            int margem_Direita = i + 1;
            while (vetor_Paises[margem_Esquerda].medalhas_Ouro == vetor_Paises[margem_Direita].medalhas_Ouro && vetor_Paises[margem_Esquerda].medalhas_Prata == vetor_Paises[margem_Direita].medalhas_Prata && margem_Direita < quantidade_Paises)
                margem_Direita++;
            i = margem_Direita - 1;

            for (int j = margem_Esquerda; j < margem_Direita; j++)
            {
                for (int k = margem_Esquerda; k < margem_Direita - 1; k++)
                {
                    if (vetor_Paises[k].medalhas_Bronze < vetor_Paises[k + 1].medalhas_Bronze)
                    {
                        TAD_aux = vetor_Paises[k];
                        vetor_Paises[k] = vetor_Paises[k + 1];
                        vetor_Paises[k + 1] = TAD_aux;
                    }
                }
            }
        }
    }
}

//Ordenação alfabética através do método bubble sort.
void bubbleSort_Alfabetica(medalhas_pais *vetor_Paises, int quantidade_Paises)
{
    medalhas_pais TAD_aux;

    for (int i = 0; i < quantidade_Paises - 1; i++)
    {
        if (vetor_Paises[i].medalhas_Ouro == vetor_Paises[i + 1].medalhas_Ouro && vetor_Paises[i].medalhas_Prata == vetor_Paises[i + 1].medalhas_Prata && vetor_Paises[i].medalhas_Bronze == vetor_Paises[i + 1].medalhas_Bronze)
        {
            int margem_Esquerda = i;
            int margem_Direita = i + 1;
            while (vetor_Paises[margem_Esquerda].medalhas_Ouro == vetor_Paises[margem_Direita].medalhas_Ouro && vetor_Paises[margem_Esquerda].medalhas_Prata == vetor_Paises[margem_Direita].medalhas_Prata && vetor_Paises[margem_Esquerda].medalhas_Bronze == vetor_Paises[margem_Direita].medalhas_Bronze)
            {
                margem_Direita++;
            }
            i = margem_Direita - 1;

            for (int j = margem_Esquerda; j < margem_Direita; j++)
            {
                for (int k = margem_Esquerda; k < margem_Direita - 1; k++)
                {
                    if (strcmp(vetor_Paises[k].nome_Pais, vetor_Paises[k + 1].nome_Pais) > 0)
                    {
                        TAD_aux = vetor_Paises[k];
                        vetor_Paises[k] = vetor_Paises[k + 1];
                        vetor_Paises[k + 1] = TAD_aux;
                    }
                }
            }
        }
    }
}

void imprimir_Quadro(medalhas_pais *vetor_Paises, int quantidade_Paises)
{
    for (int i = 0; i < quantidade_Paises; i++)
    {
        printf("%s %d %d %d\n", vetor_Paises[i].nome_Pais, vetor_Paises[i].medalhas_Ouro, vetor_Paises[i].medalhas_Prata, vetor_Paises[i].medalhas_Bronze);
    }
}