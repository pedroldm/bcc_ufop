//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

void CalcularDuracao (int HInicial, int MInicial, int HFinal, int MFinal, int *Duracao);

int main () {
    int HInicial, HFinal, MInicial, MFinal, Duracao;
    printf ("Insira a hora inicial do jogo: ");
    scanf ("%d", &HInicial);
    printf ("Insira o minuto inicial do jogo: ");
    scanf ("%d", &MInicial);
    printf ("Insira a hora final do jogo: ");
    scanf ("%d", &HFinal);
    printf ("Insira o minuto final do jogo: ");
    scanf ("%d", &MFinal);

    CalcularDuracao (HInicial, MInicial, HFinal, MFinal, &Duracao);

    printf ("O jogo durou %d minutos.", Duracao);
    return 0;
} 

void CalcularDuracao (int HInicial, int MInicial, int HFinal, int MFinal, int *Duracao) {
    if ( HInicial < HFinal ) {
        *Duracao = (( HFinal - HInicial - 1 ) * 60) + ( 60 - MInicial ) + MFinal;
    }
    else *Duracao = (( 24 - HInicial + HFinal - 1) * 60) + (60 - MInicial ) + MFinal;
}