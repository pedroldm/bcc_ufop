//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <stdlib.h>

void confereMatriz (int **Matriz, int N);
int **criarMatriz (int N);

int main (){
    int N, **Matriz;

    printf ("Digite o valor de N: ");
    scanf ("%d", &N);
    printf ("\n");

    Matriz = criarMatriz (N);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf ("Digite o valor da posição [%d][%d]: ", i+1, j+1);
            scanf ("%d", &Matriz[i][j]);
        }
    }

    confereMatriz (Matriz, N);

    liberarMatriz (Matriz, N);
    
    return 0;
}

int **criarMatriz (int N){
    int **Matriz;
    Matriz = malloc (N * sizeof(int*));
    
    for (int i = 0; i < N; i++){
        Matriz[i] = malloc (N * sizeof(int));
    }

    return Matriz;
}

void confereMatriz (int **Matriz, int N){
    int Verif = 0, *VetSomatorios, aux;

    VetSomatorios = malloc (((N * 2) + 2) * sizeof(int));

    for (int i = 0; i < N; i++){ // Inserindo o somatório de cada linha à posição correspondente no vetor.
        VetSomatorios[i] = 0;
        for (int j = 0; j < N; j++){
            VetSomatorios[i] += Matriz[i][j];
        }
    }

    for (int j = 0; j < N; j++){ // Inserindo o somatório de cada coluna às posições seguintes do vetor.
        VetSomatorios[N+j] = 0;
        for (int i = 0; i < N; i++){
            VetSomatorios[N+j] += Matriz[i][j];
        }
    }

    VetSomatorios[2 * N] = 0;
    for (int i = 0; i < N; i++){ // Inserindo o somatório da diagonal principal.
        VetSomatorios[2 * N] += Matriz[i][i];
    }

    VetSomatorios[2 * N + 1] = 0;
    for (int i = 0; i < N; i++){ // Inserindo o somatório da diagonal secundária.
        for (int j = N-1; j <= 0; j--){
            VetSomatorios[2 * N + 1] += Matriz[j][i];
        }
    }

    do {
        for (aux = 0; aux <= 2 * N; aux++){
            if (VetSomatorios[aux] == VetSomatorios[aux+1]) Verif++;
            printf ("%d ---  ", VetSomatorios[aux]);
        }
    } while (VetSomatorios[aux] == VetSomatorios[aux+1]);

    free(VetSomatorios);

    if (Verif == (2 * N)) printf ("\nEsta matriz é um quadrado mágico! :D\n");
    else printf ("\nEsta matriz não é um quadrado mágico. :(\n");
}

void liberarMatriz (int **Matriz, int N){
    for (int i = 0; i < N; i++){
        free (Matriz[i]);
    }
    
    free (Matriz);
}
