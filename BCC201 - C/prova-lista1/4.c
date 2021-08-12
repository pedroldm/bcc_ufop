#include <stdio.h>

int main (){
    double Produto, Venda;

    printf ("Insira o valor do produto: ");
    scanf ("%lf", &Produto);

    if (Produto < 20) Venda = Produto * 1.45;
    else Venda = Produto * 1.45;
    printf ("Valor de venda: %lf", Venda);

    return 0;
}