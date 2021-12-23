//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

void converterCelsius(float Celsius, float *Fahrenheit, float *Kelvin);

int main (){
    float Celsius, Fahrenheit, Kelvin;
    printf ("Insira a temperatura em graus Celsius: ");
    scanf ("%f", &Celsius);

    converterCelsius (Celsius, &Fahrenheit, &Kelvin);

    printf ("\n%.2f graus Celsius equivalem a:\n%.2f graus Fahrenheit\n%.2f graus Kelvin", Celsius, Fahrenheit, Kelvin);
    return 0;
}

void converterCelsius(float Celsius, float *Fahrenheit, float *Kelvin) {
    *Fahrenheit = 1.8 * Celsius + 32;
    *Kelvin = Celsius + 273.15;
}