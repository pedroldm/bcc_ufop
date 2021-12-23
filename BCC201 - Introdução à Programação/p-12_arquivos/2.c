//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>

typedef struct{
    char Nome[100];
    double Nota;
    double Frequencia;
} Aluno;

void escreverDados (Aluno Alunos[], int N);

int main (){
    int N;
    Aluno Alunos[100];  

    do {
    printf ("Insira o número de alunos (máximo = 100): ");
    scanf ("%d", &N);
    getchar();
    if (N < 0 || N > 100) printf ("Entrada inválida.\n");
    } while (N < 0 || N > 100);

    printf ("\n");

    for (int i = 0; i < N; i++){
        printf ("Aluno %d - Nome completo: ", i+1);
        fgets (Alunos[i].Nome, 100, stdin);
	int STam = strlen (Alunos[i].Nome) - 1;
        Alunos[i].Nome[STam] = '\0';
        printf ("Aluno %d - Nota: ", i+1);
	scanf ("%lf", &Alunos[i].Nota);
	printf ("Aluno %d - Frequencia: ", i+1);
	scanf ("%lf", &Alunos[i].Frequencia);
	getchar();
    }

    escreverDados (Alunos, N);

    return 0;
}

void escreverDados (Aluno Alunos[], int N){

    char Nome_Arquivo[50];
    int STam;

    printf ("Insira o nome do arquivo para criação/gravação: ");
    fgets (Nome_Arquivo, 50, stdin);
    STam = strlen (Nome_Arquivo) - 1;
    Nome_Arquivo[STam] = '\0';
    
    for (int i = 0; i < N; i++){
	for (int j = 0; j < strlen (Alunos[i].Nome) - 1; j++){
	    if (Alunos[i].Nome[j] == ' ') Alunos[i].Nome[j] = '_';
	}
    }

    FILE *Arquivo = fopen (Nome_Arquivo, "w");

    fprintf (Arquivo, "%d\n", N);    

    for (int i = 0; i < N; i++){
	fprintf(Arquivo, "%s %.2lf %.2lf\n", Alunos[i].Nome, Alunos[i].Nota, Alunos[i].Frequencia);
	if (i == N-1) printf ("\nDados gravados com sucesso em '%s'!\n", Nome_Arquivo);
    }    

    fclose (Arquivo);
}

        
    

