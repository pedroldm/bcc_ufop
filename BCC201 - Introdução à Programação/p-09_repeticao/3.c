//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

int main (){
    int N = 51;
    int Asterisco;

    while (N > 50 || N < 1){
    printf ("Insira N (1 < N < 50): ");
    scanf ("%d", &N);
    if (N < 1 || N > 50)  printf ("Entrada inválida.\n");
    }

    int X [N - 1];

    for (int i = 0; i < N; i++){
        printf ("Digite o valor da posição %d: ", i+1);
        scanf ("%d", &Asterisco);
        X [i] = Asterisco;
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < X[i]; j++){
            printf ("*");
        }
        printf ("\n");
    }
    
    return 0;
}