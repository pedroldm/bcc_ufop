#include <stdio.h>

int main (){
    double Conta[3];
    double Limite[3];
    double Saldo[3];
    int i;
    int j;

    for (i = 1; i <=3; i++){
        printf ("Insira a conta do cliente %d: ", i);
        scanf ("%lf", &Conta[i]);
        printf ("Insira o limite de crédito anterior do cliente %d: ", i);
        scanf ("%lf", &Limite[i]);
        printf ("Insira o saldo atual do cliente %d: ", i);
        scanf ("%lf", &Saldo[i]);
    }

    printf ("Cliente \t Novo Limite de Crédito \t Saldo atual\n");
    for (i = 1; i <=3; i++){
        double NovoLimite = Limite[i] / 2;
        printf ("%.0lf \t\t\t R$%.2lf \t\t R$%.2lf ", Conta[i], NovoLimite, Saldo[i]);
        if (Saldo[i] > NovoLimite) {
            printf ("*");
            j++;
        }
        printf ("\n");  
    }

    if (j > 0) printf ("\n* - Saldo superior ao novo limite de crédito.\n");
    return 0;
}