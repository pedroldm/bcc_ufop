// Pedro Lucas Damasceno Silva - 20.1.4003
// Turma 41 - PLE

#include <stdio.h>
#include <math.h>

int main (){

    float Peso, Altura, IMC;
    printf ("Insira seu peso em quilogramas: ");
    scanf ("%f", &Peso);
    printf ("Insira sua altura em metros: ");
    scanf ("%f", &Altura);

    IMC = Peso / pow (Altura, 2);

    if ( IMC < 18.5 ){
        printf ("Seu IMC é: %.2f - Abaixo do peso", IMC);
    }
    else if ( 18.5 <= IMC && IMC < 25 ){
        printf ("Seu IMC é: %.2f - Peso normal", IMC);
    }
    else if ( 25 <= IMC && IMC < 30 ){
        printf ("Seu IMC é: %.2f - Acima do peso", IMC);
    }
    else if ( 30 < IMC ){
        printf ("Seu IMC é: %.2f - Obeso", IMC);
    }
    return 0;
}