//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

double ConverterMoeda (double Real, double Cotacao) {
    double Conversao;
    Conversao = Real / Cotacao;
    return Conversao;
}

int main () {

    double Cotacao, Resultado, Real;
    printf ("Digite o valor em real: ");
    scanf ("%lf", &Real);
    printf ("Digite o valor de cotação do dólar: ");
    scanf ("%lf", &Cotacao);

    Resultado = ConverterMoeda (Real, Cotacao);
    printf ("O valor convertido é: %.2lf", Resultado);
    return 0;
}