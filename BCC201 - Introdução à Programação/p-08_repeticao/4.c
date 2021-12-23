#include <stdio.h>

int ValidaCPF (long long CPF);

int main (){
    long long CPF;
    printf ("Insira o CPF: ");
    scanf ("%lld", &CPF);

    if (ValidaCPF(CPF)) printf ("O CPF é válido!");
    else printf ("O CPF é inválido.");

    return 0;
}

int ValidaCPF (long long CPF){
    //Validação do primeiro dígito:
    int i = 2;
    int Resultado = 0;
    int Algarismo = 0;
    int Verificador1 = 0;
    long long Multiplicador = 1000;
    
   for (i = 2; i <= 10; i++){
       Algarismo = (CPF * 10 / Multiplicador) - ((CPF / Multiplicador) * 10);
       Algarismo *= i;
       Resultado += Algarismo;
       Multiplicador *= 10;
    }
    if ((Resultado * 10) % 11 == ((CPF / 10) % 10)) Verificador1 = 1;
    
    Resultado = 0;
    Multiplicador = 100;
    int Verificador2 = 0;

    //Validação do segundo dígito:
    for (i = 2; i <= 11; i++){
        Algarismo = (CPF * 10 / Multiplicador) - ((CPF / Multiplicador) * 10);
        Algarismo *= i;
        Resultado += Algarismo;
        Multiplicador *= 10;
    }
    if ((Resultado * 10) % 11 == (CPF % 10)) Verificador2 = 1;

    if (Verificador1 == 1 && Verificador2 == 1) return 1;
    else return 0;
}
