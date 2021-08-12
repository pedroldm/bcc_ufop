#include <stdio.h>

int main (){
    int Numeros, i;
    double H, MH, X, N;

    printf ("Cálculo da Média Harmônica.\nQuantos números você quer digitar? ");
    scanf ("%d", &Numeros);
    printf ("\n");

    i = 1;
    H = 0;
    while (i <= Numeros){
        printf ("Número %d: ", i);
        scanf ("%lf", &N);
        X = 1 / N;
        H += X;
        i++;
    }

    MH = Numeros / H;

    printf ("\nMédia Harmônica: %.2lf", MH);
    return 0;
}