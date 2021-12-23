//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

void transporMatriz (int Matriz[][10], int N);

int main (){
    int N = 0;

    do {
        printf ("Insira 'n' para a matriz quadrada A(n x n): ");
        scanf ("%d", &N);
        if (N < 1 || N > 10) printf ("Entrada inválida. 0 < n <= 10");
    } while (N < 1 || N > 10);

    int Matriz[10][10];

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf ("Insira o valor para a posição [%d][%d]: ", i+1, j+1);
            scanf ("%d", &Matriz[i][j]);
        }
    }

    transporMatriz (Matriz, N);

    return 0;
}

void transporMatriz (int Matriz[][10], int N){
    int MatrizTransposta [10][10];

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            MatrizTransposta [j][i] = Matriz [i][j];
            printf ("%d ", MatrizTransposta[i][j]);
        }
        printf ("\n");
    }
}