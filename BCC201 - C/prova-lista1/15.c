#include <stdio.h>

void troca3 (int *a, int *b, int *c);

int main (){
    int a, b, c;
    printf ("Insira A, B e C: ");
    scanf ("%d %d %d", &a, &b, &c);

    troca3 (&a, &b, &c);

    printf ("A = %d ---- B = %d ---- C = %d", a, b, c);

    return 0;
}

void troca3 (int *a, int *b, int *c){
    int A, B, C;
    A = *a;
    B = *b;
    C = *c;
    *a = B;
    *b = C;
    *c = A;
}