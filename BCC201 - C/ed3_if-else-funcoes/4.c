//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

double CalcularSalario (double Vendas) {
    double Comissao;
    if ( Vendas > 5000 ) {
        Comissao = Vendas * 0.25;
    }
    else if ( Vendas >= 2500 && 5000 >= Vendas ) {
        Comissao = Vendas * 0.2;
    }
    else if ( 2500 > Vendas ) {
        Comissao = Vendas * 0.15;
    }
    return Comissao;
}

int main () {

    double Vendas, Resultado;
    printf ("Digite o valor total das vendas: ");
    scanf ("%lf", &Vendas);

    if ( Vendas >= 0 ) {
        Resultado = CalcularSalario (Vendas);
        printf ("O valor da comissão é: %.2lf", Resultado);
    }
    else printf ("O valor total das vendas não pode ser negativo!");
}