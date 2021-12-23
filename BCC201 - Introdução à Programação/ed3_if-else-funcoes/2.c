//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <math.h>
#define PI 3.14159

double CalcularVolume (double Raio) {
    double Volume;
    Volume = (4 * PI * pow (Raio, 3)) / 3;
    return Volume;
}

int main (){

    double Raio, Resultado;
    printf ("Digite o valor do raio: ");
    scanf ("%lf", &Raio);

    if ( Raio >= 0 ) {
        Resultado = CalcularVolume (Raio);
        printf ("O volume da esfera é: %.2lf", Resultado);
    }
    else printf ("O valor do raio não pode ser negativo!");
    return 0;
}