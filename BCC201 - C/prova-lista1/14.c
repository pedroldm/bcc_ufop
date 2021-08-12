#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (){
    int A, B, Soma, Palpite;
    printf ("Palpite: ");
    scanf ("%d", &Palpite);

    srand (time(NULL));

    A = rand()%6 + 1;
    B = rand()%6 + 1;

    Soma = A + B;

    printf ("Dado A = %d | Dado B = %d | Soma = %d", A, B, Soma);
    if (Soma == Palpite) printf ("\nVocê acertou!");
    else printf ("\nVocê errou.");

    return 0;
}