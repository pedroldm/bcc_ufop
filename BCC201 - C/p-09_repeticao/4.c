//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

int main (){
    int N = 101;

    while (N > 100 || N <= 0){
        printf ("Insira o número de alunos (0 < n < 100):" );
        scanf ("%d", &N);
        if (N > 100 || N <=0) printf ("Entrada inválida.\n");
    }

    double Notas1 [N-1], Notas2 [N-1];

    for (int i = 0; i < N; i++){
        printf ("Aluno %d - Insira a nota da prova 01: ", i+1);
        scanf ("%lf", &Notas1[i]);
        printf ("Aluno %d - Insira a nota da prova 02: ", i+1);
        scanf ("%lf", &Notas2[i]);
    }

    for (int i = 0; i < N; i++){
        printf ("Média do aluno %d: %.2lf - ", i+1, (Notas1[i] + Notas2[i]) / 2);
        if ((Notas1[i] + Notas2[i]) / 2 >= 60) printf ("Aprovado!\n");
        else printf ("Reprovado.\n");
    }   
    
    return 0;
}