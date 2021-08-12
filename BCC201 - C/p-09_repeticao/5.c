//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

void maior_menor (int N, int *valores, int *maior, int *menor);

int main (){
    int maior, menor, N = 1001;

    while (N > 1000){
    printf ("Insira N (máximo = 1000): ");
    scanf ("%d", &N);
    if (N > 1000 || N <=0 ) printf ("Entrada inválida.");
    }

    int valores [N - 1], Nro;

    for (int i = 0; i < N; i++){
        printf ("Insira um número inteiro para a posição %d: ", i+1);
        scanf ("%d", &Nro);
        valores [i] = Nro;
    }

    maior_menor (N, valores, &maior, &menor);

    printf ("Maior: %d\nMenor: %d", maior, menor);
    
    return 0;
}

void maior_menor (int N, int *valores, int *maior, int *menor){
    *maior = valores [0];
    *menor = valores [0];

    for (int i = 1; i < N; i++){
        if (valores [i] > *maior) *maior = valores [i];
        if (valores [i] < *menor) *menor = valores [i];
    }
}
