//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <math.h>

int calculaRaizes (double A, double B, double C, double *Delta, double *raiz1, double *raiz2);

int main () {
    double A, B, C, Delta, raiz1, raiz2;
    printf ("Insira os valores de A, B e C: ");
    scanf ("%lf %lf %lf", &A, &B, &C);

    calculaRaizes (A, B, C, &Delta, &raiz1, &raiz2);
    
    if ( calculaRaizes (A, B, C, &Delta, &raiz1, &raiz2) ) {
        if ( raiz1 != raiz2 ){
            printf ("X = %.2lf\nX' = %.2lf", raiz1, raiz2);
        }
        else printf ("X = %.2lf -- Apenas uma raíz real (Delta = 0)", raiz1);
    }
    else printf ("Não há raízes reais (Delta < 0)");
    return 0;
}

int calculaRaizes (double A, double B, double C, double *Delta, double *raiz1, double *raiz2) {
    *Delta = pow (B,2) - 4 * A * C;
    if ( *Delta >= 0 ) {
        *raiz1 = ((-B) + sqrt(*Delta)) / (2 * A);
        *raiz2 = ((-B) - sqrt(*Delta)) / (2 * A);
    	 return 1;
    }
    else return 0;
}
