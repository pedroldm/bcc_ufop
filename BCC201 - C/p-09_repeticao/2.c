//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

int main (){
    double N [6], X;
    int Verificador = 0;

    for (int i = 0; i <= 6; i++){
        printf ("Insira um número para a posição %d do vetor: ", i);
        scanf ("%lf", &X);
        N[i] = X;
    }

    printf ("Número a ser pesquisado: ");
    scanf ("%lf", &X);

    for (int i = 0; i <= 6; i++){
        if (N[i] == X) Verificador++;
    }

    if (!Verificador) printf ("Não encontrado.");
    else printf ("Encontrado!");
    
    return 0;
}