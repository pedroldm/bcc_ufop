#include <stdio.h>

int main (){
    double Unidade, Soma, N, Denominador = 1, Sinal = 1;

    printf ("Insira N: ");
    scanf ("%lf", &N);

    for ( int i = 1; i <= N; i++ ){
    Unidade = (Sinal * 1) / Denominador;
    Soma += Unidade;
    Sinal *= -1;
    Denominador += 2;
    }

    printf ("H = %lf", Soma);
    return 0;

}