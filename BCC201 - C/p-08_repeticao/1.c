#include <stdio.h>

int main()
{
    double Numero;
    int Positivos, Negativos;

    Numero = 1;
    Positivos = 0;
    Negativos = 0;
    while (Numero != 0){
        printf ("DIGITE UM NÚMERO REAL (PARAR = 0): ");
        scanf ("%lf", &Numero);
        if (Numero < 0) Negativos++;
        if (Numero > 0) Positivos++;
    }

    printf ("\nQUANTIDADE DE POSITIVOS DIGITADOS: %d", Positivos);
    printf ("\nQUANTIDADE DE NEGATIVOS DIGITADOS: %d", Negativos);
    return 0;
}