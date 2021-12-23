#include <stdio.h>

int main (){
    double N, j, i, Unidade, Soma;

    printf ("Insira N: ");
    scanf ("%lf", &N);

    i = 1;
    j = 0;
    Soma = 0;
    
    while ((N + j) != 0){
        Unidade = (i / (N + j));
        Soma += Unidade;
        i++;
        j--;
    }

    while (j <= 0){
        Unidade = (N + j) / i;
        Soma += Unidade;
        i--;
        j++;
    }

    printf ("H = %lf\n", Soma);
    
    return 0;
}