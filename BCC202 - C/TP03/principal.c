#include "buscabinaria.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    long n, a, soma_Total;
    double h;
    int *v_Tiras = NULL;

    while (scanf("%ld %ld", &n, &a))
    {
        if (n == 0 && a == 0)
            break;

        v_Tiras = alocaVetor(v_Tiras, n);

        soma_Total = 0;

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &v_Tiras[i]);
            soma_Total += v_Tiras[i];
        }

        if (soma_Total == a)
            printf(":D\n");
        else if (soma_Total < a)
            printf("-.-\n");
        else
        {
            particionarVetor(v_Tiras, 0, n - 1); // ---- OK.
            h = buscaBinaria(v_Tiras, n, a);
            printf("%.4lf\n", h);
        }

        v_Tiras = desalocaVetor(v_Tiras);
    }

    return 0;
}