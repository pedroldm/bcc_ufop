/*
Pedro Lucas Damasceno Silva - 20.1.4003
BCC202-P 2020.2
Aula Prática 0 - Manipulação de Matrizes Estáticas
*/

#include <stdio.h>
int main()
{
    double M[12][12], somaTotal = 0;
    int j;
    char charOperacao;

    scanf ("%c", &charOperacao);

    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 12; j++){
            scanf ("%lf", &M[i][j]);
        }
    }

    for (int i = 0; i < 5; i++){
        j = i+1;
        while (j < 11-i){
            somaTotal += M[i][j];
            j++;
        }
    }
    
    if (charOperacao == 'S') printf ("%.1lf", somaTotal);
    else printf ("%.1lf", somaTotal/30);

    return 0;
}