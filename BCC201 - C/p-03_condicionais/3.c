#include <stdio.h>

int main ()
{
    int A, B, C;
    printf("Insira três números: ");
    scanf("%d %d %d", &A, &B, &C);

    if ( A > B && B > C ) 
    {
        printf("Menor: %d\nIntermediário: %d\nMaior: %d", C, B, A);
    }
    else if ( A > C && C > B )
    {
        printf("Menor: %d\nIntermediário: %d\nMaior: %d", B, C, A);
    }
    else if ( B > A && A > C )
    {
        printf("Menor: %d\nIntermediário: %d\nMaior: %d", C, A, B);
    }
    else if ( B > C && C > A )
    {
        printf("Menor: %d\nIntermediário: %d\nMaior: %d", A, C, B);
    }
    else if ( C > A && A > B )
    {
        printf("Menor: %d\nIntermediário: %d\nMaior: %d", B, A, C);
    }
    else if ( C > B && B > A )
    {
        printf("Menor: %d\nIntermediário: %d\nMaior: %d", A, B, C);
    }
    return 0;
}