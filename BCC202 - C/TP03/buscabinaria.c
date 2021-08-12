#include <stdio.h>
#include <stdlib.h>

int *alocaVetor(int *v_Tiras, int n)
{
    v_Tiras = (int *)malloc(n * sizeof(int));
    if (v_Tiras == NULL)
    {
        printf("Memória insuficiente.\n");
        exit(1);
    }

    return v_Tiras;
}

int *desalocaVetor(int *v_Tiras)
{
    free(v_Tiras);
    return NULL;
}

void mergeSort(int *vetor, int margem_Esquerda, int nova_Margem, int n)
{
    int tamanho_Esquerda = (nova_Margem - margem_Esquerda + 1), tamanho_Direita = (n - nova_Margem);
    int *vetor_Esquerda = (int *)malloc(tamanho_Esquerda * sizeof(int));
    int *vetor_Direita = (int *)malloc(tamanho_Direita * sizeof(int));
    int i, j;

    for (i = 0; i < tamanho_Esquerda; i++)
        vetor_Esquerda[i] = vetor[i + margem_Esquerda];

    for (j = 0; j < tamanho_Direita; j++)
        vetor_Direita[j] = vetor[nova_Margem + j + 1];

    i = 0, j = 0;

    for (int k = margem_Esquerda; k <= n; k++)
    {
        if (i == tamanho_Esquerda)
            vetor[k] = vetor_Direita[j++];
        else if (j == tamanho_Direita)
            vetor[k] = vetor_Esquerda[i++];
        else if (vetor_Esquerda[i] < vetor_Direita[j])
            vetor[k] = vetor_Esquerda[i++];
        else
            vetor[k] = vetor_Direita[j++];
    }

    free(vetor_Direita);
    free(vetor_Esquerda);
}

void particionarVetor(int *vetor, int margem_Esquerda, int n)
{
    if (margem_Esquerda < n)
    {
        int nova_Margem = (margem_Esquerda + n) / 2;
        particionarVetor(vetor, margem_Esquerda, nova_Margem);
        particionarVetor(vetor, nova_Margem + 1, n);
        mergeSort(vetor, margem_Esquerda, nova_Margem, n);
    }
}

double calcularArea(int *v_Tiras, int n, double h)
{
    double somar_Area = 0;

    for (int i = n - 1; i > -1; i--)
    {
        if (v_Tiras[i] > h)
            somar_Area += (v_Tiras[i] - h);
        else
            break;
    }

    return somar_Area;
}

double buscaBinaria(int *v_Tiras, int n, int a)
{
    double margem_Superior = v_Tiras[n - 1];
    double margem_Inferior = 0;
    double area = 0;
    double h;

    for (int i = 0; i < 30; i++)
    {
        h = (margem_Superior + margem_Inferior) / 2;
        area = calcularArea(v_Tiras, n, h);

        if (area < a)
            margem_Superior = h;
        else
            margem_Inferior = h;
    }

    return h;
}