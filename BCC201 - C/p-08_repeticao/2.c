#include <stdio.h>
#include <math.h>

double CalculaPi (int N);

int main()
{
    int N;
    double Pi;

    printf ("Insira o número de termos: ");
    scanf ("%d", &N);

     Pi = CalculaPi (N);

    printf ("Para %d termos, Pi = %llf", N, Pi);
    return 0;

}

double CalculaPi (int N){
    int aux;
    double Divisor, Soma, S, Unidade, Pi;
    Divisor = 3;
    Soma = 0;
    for (aux = 1; aux <= N; aux++){
        Unidade = 1 / pow (Divisor, 3);
        Divisor += 2;
        if (aux % 2 == 0)Soma -= Unidade;
        else Soma += Unidade;
    }
    S = 1 - Soma;
    Pi = cbrt (S * 32);
    return Pi;
}