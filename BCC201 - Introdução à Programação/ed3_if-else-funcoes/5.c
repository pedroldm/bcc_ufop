//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double Somar (double X, double Y) {
    return X + Y;
}
double Subtrair (double X, double Y) {
    return X - Y;
}
double Multiplicar (double X, double Y) {
    return X * Y;
}
double Dividir (double X, double Y) {
    if ( Y != 0 ){
        return X / Y;
    }
    else {
        printf ("Erro: Divisão por zero !");
        abort ();
    }
}
double Potenciar (double X, double Y) {
    return pow (X, Y);
}

int main () {

    double X, Y, Resultado;
    char L;
    printf ("Digite o primeiro valor: ");
    scanf ("%lf", &X);
    printf ("Digite o segundo valor: ");
    scanf ("%lf", &Y);
    printf ("Informe a operação: ");
    scanf (" %c", &L);

    switch (L) {
        case '+': Resultado = Somar (X, Y);
        break;
        case '-': Resultado = Subtrair (X, Y);
        break;
        case '*': Resultado = Multiplicar (X, Y);
        break;
        case '/': Resultado = Dividir (X, Y);
        break;
        case '^': Resultado = Potenciar (X, Y);
    }
    
    printf ("%.2lf %c %.2lf = %.2lf", X, L, Y, Resultado);
    return 0;
}