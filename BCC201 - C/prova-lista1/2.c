#include <stdio.h>

int main (){
    double A, B, C;

    printf ("Insira 3 números reais: ");
    scanf ("%lf %lf %lf", &A, &B, &C);

    if (A > B && B > C) printf ("%lf - %lf - %lf", C, B, A);
    else if (A > C && C > B) printf ("%lf - %lf - %lf", B, C, A);
    else if (B > A && A > C) printf ("%lf - %lf - %lf", C, A, B);
    else if (B > C && C > A) printf ("%lf - %lf - %lf", A, B, C);
    else if (C > A && A > B) printf ("%lf - %lf - %lf", B, A, C);
    else if (C > B && B > A) printf ("%lf - %lf - %lf", A, B, C);

    return 0;
}