//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>

typedef struct {
    char Nome [100];
    double Nota;
    double Frequencia;
} Aluno;

void traduzirBinario (char Nome[], char NomeBinario[], int STam, int *N);
void lerBinario (char NomeBinario[], int *N, Aluno Alunos[]);

int main (){
    char Nome[50], NomeBinario[50];
    int STam, N;
    Aluno Alunos[100];
    
    printf ("Digite o nome do arquivo texto: ");
    fgets (Nome, 50, stdin);
    STam = strlen (Nome) - 1;
    Nome[STam] = '\0';

    strcpy (NomeBinario, Nome);
    NomeBinario[STam-1] = 't';
    NomeBinario[STam-2] = 'a';
    NomeBinario[STam-3] = 'd';

    traduzirBinario (Nome, NomeBinario, STam, &N);
    printf ("Arquivo %s criado com sucesso!\n\n", NomeBinario);
    lerBinario (NomeBinario, &N, Alunos);

    return 0;
}

void traduzirBinario (char Nome[], char NomeBinario[], int STam, int *N){
    FILE *ArquivoTXT, *ArquivoBinario;
    char AlunoNome[100];
    double Nota, Frequencia;

    ArquivoTXT = fopen (Nome, "r");
    ArquivoBinario = fopen (NomeBinario, "wb");

    fscanf (ArquivoTXT, "%d", &*N);
    fwrite (&N, sizeof(int), 1, ArquivoBinario);

    for (int i = 0; i < *N; i++){
	fscanf (ArquivoTXT, "%s %lf %lf", AlunoNome, &Nota, &Frequencia);
        fwrite (AlunoNome, sizeof(char), 100, ArquivoBinario);
	fwrite (&Nota, sizeof(double), 1, ArquivoBinario);
	fwrite (&Frequencia, sizeof(double), 1, ArquivoBinario);
    }

    fclose (ArquivoTXT);
    fclose (ArquivoBinario);
}

void lerBinario (char NomeBinario[], int *N, Aluno Alunos[]){
    FILE *ArquivoBinario = fopen (NomeBinario, "rb");
    double SomaNotas = 0, SomaFrequencia = 0, Aprovados = 0;

    fread (&N, sizeof(int), 1, ArquivoBinario);
    
    for (int i = 0; i < *N; i++){
	fread (Alunos[i].Nome, sizeof(char), 100, ArquivoBinario);
	    for (int j = 0; j < strlen (Alunos[i].Nome); j++){
	        if (Alunos[i].Nome[j] == '_') Alunos[i].Nome[j] = ' ';
	    }
        fread (&Alunos[i].Nota, sizeof(double), 1, ArquivoBinario);
        SomaNotas += Alunos[i].Nota;
	    fread (&Alunos[i].Frequencia, sizeof(double), 1, ArquivoBinario);
        SomaFrequencia += Alunos[i].Frequencia;
	    if (Alunos[i].Frequencia >= 75 && Alunos[i].Nota >= 6){
	        Aprovados++;
        }
    }

    fclose (ArquivoBinario);

    printf ("Nota média: %.1lf\nFrequência média: %.0lf%%\nPercentual de aprovação: %.0lf%%\n\n", SomaNotas / *N, SomaFrequencia / *N, (Aprovados / *N) * 100);

    printf ("Nomes dos alunos com nota acima da média:\n");

    for (int i = 0; i < *N; i++){
        if (Alunos[i].Nota > (SomaNotas / *N)){
            printf ("%s\n", Alunos[i].Nome);
        }
    }   
}