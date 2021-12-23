//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>

typedef struct {
    char NomeCompleto [100];
    int Matricula;
    double Notas [10];
} Aluno;

Aluno encontraAluno (Aluno alunos[], int nAlunos);

int main (){
    int nAlunos, M, opcao = 0, matricula;
    Aluno alunos [100];
    Aluno X [1];
    double MediaNotas, Soma = 0;

    do {
        printf ("Insira N: ");
        scanf ("%d", &nAlunos);
        if (nAlunos > 100 || nAlunos < 1) printf ("Entrada inválida.\n");
    } while (nAlunos > 100 || nAlunos < 1);

    do {
        printf ("Insira M: ");
        scanf ("%d", &M);
        getchar();
        if (M > 10 || M < 1) printf ("Entrada inválida.\n");
    } while (M > 10 || M < 1);

    for (int i = 0; i < nAlunos; i++){
        printf ("Insira o nome completo do %dº aluno: ", i+1);
        fgets (alunos[i].NomeCompleto, 100, stdin);
        int TS = strlen (alunos[i].NomeCompleto) - 1;
        alunos[i].NomeCompleto[TS] = '\0';

        printf ("Insira o número de matrícula: ");
        scanf ("%d", &alunos[i].Matricula);
        
        for (int j = 0; j < M; j++){
            printf ("Insira a %dº nota: ", j+1);
            scanf ("%lf", &alunos[i].Notas[j]);
            if (j == (M-1)) getchar();
        }
    }

    for (int i = 0; i < nAlunos; i++){
        for (int j = 0; j < M; j++){
            Soma += alunos[i].Notas[j];
        }
    }

    MediaNotas = Soma / (M * nAlunos);

    printf ("Média geral: %.2lf", MediaNotas);

    Soma = 0;

    X[1] = encontraAluno (alunos, nAlunos);

    for (int i = 0; i < M; i++){
        Soma += X[1].Notas[i];
    }

    MediaNotas = Soma / M;
    
    printf ("Aluno: %s - Matrícula: %d - Média: %.2lf", X[1].NomeCompleto, X[1].Matricula, MediaNotas);

    return 0;
}

Aluno encontraAluno (Aluno alunos[], int nAlunos){
    int i, matricula;

    do {
        printf ("\nInsira um número de matrícula: ");
        scanf ("%d", &matricula);

        i = 0;
        while (alunos[i].Matricula != matricula && i <= nAlunos){
            i++;
            printf ("i = %d\n", i);
        }

        if (i > nAlunos) printf ("Matrícula não encontrada.");
    } while (alunos[i].Matricula != matricula);

    return alunos[i];
} 
