//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

long long fat(int n);

int main()
{

    int N;
    int Verificador = 0;
    long long Resultado;
    
    while (!Verificador)
    {
        printf("Digite o valor de n: ");
        scanf("%d", &N);
        if (N < 0)
            printf("\nO fatorial não admite números negativos.\n\n");
        else
            Verificador = 1;
    }

    Resultado = fat(N);

    printf("%d! = %lld", N, Resultado);
    return 0;
}

long long fat(int n)
{
    long long Fatorial;
    Fatorial = 1;
    while (n > 1)
    {
        Fatorial *= n--;
    }
    return Fatorial;
}