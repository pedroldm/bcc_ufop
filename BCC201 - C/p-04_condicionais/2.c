// Pedro Lucas Damasceno Silva - 20.1.4003
// Turma 41 - PLE

#include <stdio.h>

int main(){

    int Idade;
    printf ("Insira a idade: ");
    scanf ("%d", &Idade);

    if ( Idade <= 10 ){
        printf ("Valor da mensalidade: R$90.00");
    }
    else if ( 10 < Idade && Idade <= 29 ){
        printf ("Valor da mensalidade: R$170.00");
    }
    else if ( 29 < Idade && Idade <= 45 ){
        printf ("Valor da mensalidade: R$290.00");
    }
    else if ( 45 < Idade && Idade <= 59 ){
        printf ("Valor da mensalidade: R$400.00");
    }
    else if ( 59 < Idade && Idade <= 65 ){
        printf ("Valor da mensalidade: R$515.00");
    }
    else if (65 < Idade){
        printf ("Valor da mensalidade: R$695.00");
    }
    return 0;
}