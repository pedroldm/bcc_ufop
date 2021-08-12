#include <stdio.h>

int main ()
{
    int Ano;
    printf("Insira o ano: ");
    scanf("%d", &Ano);

    if ( Ano % 4 == 0 && Ano % 100 != 0 || Ano % 100 == 0 && Ano % 400 == 0)
    {
        printf("O ano é bissexto!");
    }
    else printf("O ano não é bissexto.");
    return 0;
}