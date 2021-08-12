#include <stdio.h>
#include <math.h>

void Funcao (double *A, double *Inteira, double *Decimal);

int main (){
    double A, Inteira, Decimal;
    printf ("Insira um número: ");
    scanf ("%lf", &A);

    Funcao (&A, &Inteira, &Decimal);

    printf ("Inteira: %.0lf\nDecimal: %lf", Inteira, Decimal);
}

void Funcao (double *A, double *Inteira, double *Decimal){
    *Inteira = floor (*A);
    *Decimal = *A - floor (*A);
}