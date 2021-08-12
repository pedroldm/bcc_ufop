//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

int somarColuna (int Matriz[][3]);
int multLinha (int Matriz[][3]);
int somarMatriz (int Matriz[][3]);

int main (){
    int Matriz [3][3], SomaColuna, MultLinha, SomaMatriz;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf ("Insira a posição [%d][%d]: ", i+1, j+1);
            scanf ("%d", &Matriz[i][j]);
        }
    }

    SomaColuna = somarColuna(Matriz);
    MultLinha = multLinha (Matriz);
    SomaMatriz = somarMatriz (Matriz);

    printf ("Soma dos elementos da primeira coluna: %d\nProduto dos elementos da primeira linha: %d\nSoma de todos os elementos: %d", SomaColuna, MultLinha, SomaMatriz);
    return 0;
}

int somarColuna (int Matriz[][3]){
    int R = 0;
    for (int j = 0; j < 3; j++){
        R += Matriz[j][0];
    }
    return R;
}

int multLinha (int Matriz[][3]){
    int R = 1;
    for (int i = 0; i < 3; i++){
        R *= Matriz[0][i];
    }
    return R;
}

int somarMatriz (int Matriz[][3]){
    int R = 0;
    for (int i = 0; i <= 2; i++){
        for (int j = 0; j <= 2; j++){
            R += Matriz[j][i];
        }
    }
    return R;
}