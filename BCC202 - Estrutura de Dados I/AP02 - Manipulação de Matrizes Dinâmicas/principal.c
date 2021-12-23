/*
Pedro Lucas Damasceno Silva
BCC202 - P
Aula Prática 2 - Manipulação de Matrizes Dinâmicas
*/

#include "matriz.h"
#include <stdio.h>

int main()
{
    double **M = NULL, resultado;
    int ordem;
    char operacao;

    lerOrdem(&ordem);
    lerOperacao(&operacao);
    M = alocaMatriz(M, ordem);
    lerMatriz(M, ordem);
    resultado = somaMatriz(M, ordem);
    if(operacao == 'M')
      resultado = media(resultado, ordem);
    printResultado(resultado);
    M = desalocaMatriz(M, ordem);
    
    return 0;
}
