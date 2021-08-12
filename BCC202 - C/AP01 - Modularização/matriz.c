#include "matriz.h"
#include <stdio.h>

void lerOperacao(char *operacao){
	scanf ("%c", operacao);
}

void lerMatriz(double M[][12]){
	for (int i = 0; i < 12; i++){
        	for (int j = 0; j < 12; j++){
            		scanf ("%lf", &M[i][j]);
        }
    }
}

double somaMatriz(double M[][12]){
	double somaTotal = 0;

	for (int i = 0; i < 5; i++){
        	for (int j = i + 1; j < 11 - i; j++){
            		somaTotal += M[i][j];
        	}
    }
	
	return somaTotal;
}

double media(double resultado){
	return resultado /= 30;
}

void printResultado(double resultado){
	printf ("%.1lf", resultado);
}
