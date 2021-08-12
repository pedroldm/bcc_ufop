//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <math.h>
#define PI 3.14159

double CalcularAreaC (int Raio) {
	double Area;
	Area = PI * pow(Raio, 2);
    return Area;
}

int main (){

    int Raio;
    double Resultado;
    
	printf ("Digite o valor do raio: ");
	scanf ("%d", &Raio);
    
	if ( Raio >= 0 ) {
	    Resultado = CalcularAreaC (Raio);
        printf ("A área do círculo é: %.2lf", Resultado);
    }
    else printf("\nO valor do raio não pode ser negativo.");
    return 0;
}