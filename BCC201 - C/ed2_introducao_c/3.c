#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
    int A, B, SOMA;

    srand(time(NULL));

    A = 1 + (rand()%6);
    B = 1 + (rand()%6);
    SOMA = A + B;

    printf("Lançamento dos dados: %d e %d\nSoma:%d", A, B, SOMA);
    return 0;
}
