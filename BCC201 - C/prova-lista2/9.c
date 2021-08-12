#include <stdio.h>

int main (){
    double Soma, Unidade, N, i;
    printf ("Insira N: ");
    scanf ("%lf", &N);

    Soma = 0;
    i = 1;
    while (i <= N){
        Unidade = (1 / i);
        Soma += Unidade;
        printf ("\n Soma = %lf\nUnidade = %lf", Soma, Unidade);
        i++;
    }

    printf ("H = %.2lf", Soma);
    return 0;
}