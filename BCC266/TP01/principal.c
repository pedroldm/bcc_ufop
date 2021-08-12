#include <stdio.h>
#include "maquina.h"

int main (){
    int **matrizRAM = NULL;

    matrizRAM = alocaMatriz(matrizRAM);
    printf ("\n");
    preencherRAM (matrizRAM);
    ordenamentoExecucao (matrizRAM);
    desalocaMatriz (matrizRAM);

    return 0;
}