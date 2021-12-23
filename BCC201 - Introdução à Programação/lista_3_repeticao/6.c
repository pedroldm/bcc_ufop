#include <stdio.h>
#include <stdlib.h>

int main (){
    int A, B, SImpar = 0, PPar = 1, Quantidade = 0, Verificador = 0;
    double MImpar;

    while (Verificador == 0){
    printf ("Insira o limite inferior (a): ");
    scanf ("%d", &A);
    printf ("Insira o limite superior (b): ");
    scanf ("%d", &B);
    if (B > A) Verificador = 1;
    else printf ("B deve ser maior que A!");
    }

    while (A <= B){
        if (A % 2 == 0) PPar *= A;
        else {
            SImpar += A;
            Quantidade++;
        }
        A++;
    }

    MImpar = SImpar / Quantidade;

    printf ("\nMédia dos ímpares: %.2lf\nProduto dos pares: %d", MImpar, PPar);

    return 0;

}