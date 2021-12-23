#include "fib.h"
#include<stdio.h>

int main()
{
    TADfib f;
    int n;

    scanf ("%d", &n);

    for (int i = 0; i < n; i++){
        scanf ("%d", &f.i);
        f.chamadas = -1;
        f.resultado = fibonacci (f.i, &f); // Processar antes de ler o próximo.
        printf ("fib(%d) = %ld chamadas = %ld\n", f.i, f.chamadas, f.resultado);
    }
    
    return 0;
}