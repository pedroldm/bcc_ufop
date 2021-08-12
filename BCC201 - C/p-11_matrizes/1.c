//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

void multMatrizes (int A[][10], int B[][10], int N, int M, int P);
void lerMatrizes (int N, int M, int P, int Q, int A[][10], int B[][10]);

int main (){
    int N, M, P, Q, A[10][10], B[10][10];

    do {
    printf ("Atenção! Condições de valores: P = Q | 10 >= P, Q, M, N\n");
    printf ("Insira as dimensões da matriz A (m x p): ");
    scanf ("%d %d", &M, &P);
    printf ("Insira as dimensões da matriz B (q x n): ");
    scanf ("%d %d", &Q, &N);
    if (P != Q || M < 1 || M > 10 || N < 1 || N > 10 || P < 1 || P > 10 || Q < 1 || Q > 10) printf ("Entrada inválida.\n");
    } while (P != Q || M < 1 || M > 10 || N < 1 || N > 10 || P < 1 || P > 10 || Q < 1 || Q > 10);

    lerMatrizes (N, M, P, Q, A, B);

    multMatrizes (A, B, N, M, P);

    return 0;
}

void lerMatrizes (int N, int M, int P, int Q, int A[][10], int B[][10]){
    for (int i = 0; i < M; i++){
        for (int j = 0; j < P; j++){
            printf ("Insira o elemento de A[%d][%d]: ", i+1, j+1);
            scanf ("%d", &A[i][j]);
        }
    }

    for (int i = 0; i < Q; i++){
        for (int j = 0; j < N; j++){
            printf ("Insira o elemento de B[%d][%d]: ", i+1, j+1);
            scanf ("%d", &B[i][j]);
        }
    }
}

void multMatrizes (int A[][10], int B[][10], int N, int M, int P){
    int C[10][10];

    printf ("Matriz C (A x B):\n");

    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            C[i][j] = 0;
            for (int k = 0; k < P; k++){
                C[i][j] += A[i][k] * B[k][j];;
            }
            printf ("%d ", C[i][j]);
        }
        printf ("\n");
    }
}