#include "ordenacao.h"
#include <stdio.h>

/* 
    Trabalho Prático 02 - BCC202P
    Pedro Lucas Damasceno Silva - 20.1.4003
*/

int main()
{
    int quantidade_Paises;
    medalhas_pais *vetor_Paises = NULL;

    ler_Quantidade(&quantidade_Paises);
    vetor_Paises = alocar_Vetor(vetor_Paises, quantidade_Paises);
    ler_Medalhas(vetor_Paises, quantidade_Paises);
    //Ordenação --
    selectionSort_Ouro(vetor_Paises, quantidade_Paises);
    bubbleSort_Prata(vetor_Paises, quantidade_Paises);
    bubbleSort_Bronze(vetor_Paises, quantidade_Paises);
    bubbleSort_Alfabetica(vetor_Paises, quantidade_Paises);
    //--
    imprimir_Quadro(vetor_Paises, quantidade_Paises);
    vetor_Paises = desalocar_Vetor(vetor_Paises);

    return 0;
}