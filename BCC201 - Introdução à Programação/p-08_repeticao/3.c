//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

int main()
{
    int X, Y;
    int i = 0;
    int Linha;
    int j = 0;
    int Verificador = 0;

    while (!Verificador) {
        printf("Digite os valores de X e Y: ");
        scanf("%d %d", &X, &Y);
        if (X < Y) {
            if (X % 2 == 0 && Y % 2 == 0) Verificador = 1;
            else printf("Apenas números pares são aceitos.");
        }
        else printf("X deve ser menor que Y.");
    }

    Linha = ((Y - X) / 2) + 1;
    int Asterisco = Y;

    printf ("\n\n");

    while (i < Linha)
    {
        while (j < Asterisco)
        {
            printf("*");
            j++;
        }
        j = 0;
        Asterisco -= 2;
        printf("\n");
        i++;
    }
    return 0;
}