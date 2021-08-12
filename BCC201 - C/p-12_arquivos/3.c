//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char Nome[100];
    double Nota;
    double Frequencia;
    int Aprovacao;
} Aluno;

void analisarAprovacoes (char Nome[], int *N, Aluno Alunos[]);

int main (){
    char Nome[50];
    int STam, N;
    Aluno Alunos[100];

    printf ("Digite o nome do arquivo: ");
    fgets (Nome, 50, stdin);
    STam = strlen (Nome) - 1;
    Nome[STam] = '\0';

    analisarAprovacoes (Nome, &N, Alunos);
    return 0;
}

void analisarAprovacoes (char Nome[], int *N, Aluno Alunos[]){
    int Aprovados;
    double SomaNotas = 0, SomaFrequencia = 0, MediaNotas, MediaFrequencia, Percentual;
    char C = 37;

    FILE *Arquivo = fopen (Nome, "r");

    if (fopen(Nome, "r") == 0){
        printf("Erro! Argumento inexistente ou arquivo não encontrado.\n");
        exit (1);
    }

    fscanf (Arquivo, "%d", &*N);

    for (int i = 0; i < *N; i++){
	fscanf (Arquivo, "%s %lf %lf", Alunos[i].Nome, &Alunos[i].Nota, &Alunos[i].Frequencia);
        SomaNotas += Alunos[i].Nota;
        SomaFrequencia += Alunos[i].Frequencia;
        if (Alunos[i].Nota >= 6 && Alunos[i].Frequencia >= 75) {
	Alunos[i].Aprovacao = 1;
        Aprovados++;
	}
    }

    for (int i = 0; i < *N; i++){
	for (int j = 0; j < strlen (Alunos[i].Nome); j++){
	    if (Alunos[i].Nome[j] == '_') Alunos[i].Nome[j] = ' ';
	}
    }

    MediaNotas = SomaNotas / *N;
    MediaFrequencia = SomaFrequencia / *N;
    Percentual = Aprovados / *N;
	
    printf ("\nNota média: %.1lf\nFrequência média: %.0lf%c\nPercentual de aprovação: %.0lf%c", MediaNotas, MediaFrequencia, C, Percentual * 100, C);
    printf ("\n\nNomes dos alunos com nota acima da média: \n");

    for (int i = 0; i < Aprovados; i++){
	if (Alunos[i].Aprovacao == 1) printf ("%s\n", Alunos[i].Nome);
    }

}
