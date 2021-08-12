// Pedro Lucas Damasceno Silva - 20.1.4003
// Turma 41 - PLE

#include <stdio.h>

int main (){
    
    float Salario, STotal;
    int Cargo;
    printf ("Insira o salário: ");
    scanf ("%f", &Salario);
    printf ("Insira o código do cargo do funcionário (100, 101, 102 ou 201): ");
    scanf ("%d", &Cargo);

    if ( Cargo == 100  ||  Cargo == 101  ||  Cargo == 102  ||  Cargo == 201 ){
        switch ( Cargo ) {
        case 100: STotal = Salario * 1.03;
        break;
        case 101: STotal = Salario * 1.05;
        break;
        case 102: STotal = Salario * 1.075;
        break;
        case 201: STotal = Salario * 1.1;
        break;
        }
        printf ("Salário corrigido: R$%.2f", STotal);
    }
    else printf ("Código de cargo inválido");
    return 0;
}