#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

void lerOrdem(int *ordem){
    scanf ("%d", ordem);
}

double **alocaMatriz(double **M, int ordem){
    M = malloc (ordem * sizeof(int*));

    if (M == NULL){
        printf ("Memória insuficiente.\n");
        exit (1);
    }
    for (int i = 0; i < ordem; i++){
        M[i] = malloc (ordem * sizeof(double));
        if (M == NULL){
            printf ("Memória insuficiente.\n");
            exit (1);
        }
    }

    return M;
}

double **desalocaMatriz(double **M, int ordem){
    for (int i = 0; i < ordem; i++){
        free (M[i]);
    }
    free (M);

    return NULL;
}

void lerOperacao(char *operacao){
    scanf (" %c", operacao);
}

void lerMatriz(double **M, int ordem){
    for (int i = 0; i < ordem; i++){
        for (int j = 0; j < ordem; j++){
            scanf ("%lf", &M[i][j]);
        }
    }
}

double somaMatriz(double **M, int ordem){
    double somaTotal = 0;

    for (int i = 0; i < (ordem/2) - 1; i++){
        for (int j = i + 1; j < (ordem - 1) - i; j++){
            somaTotal += M[i][j];
        }
    }

    return somaTotal;
}

double media(double resultado, int ordem){
    return resultado / ((ordem/2) * ((ordem/2)-1));
}

void printResultado(double resultado){
    printf ("%.1lf", resultado);
}
