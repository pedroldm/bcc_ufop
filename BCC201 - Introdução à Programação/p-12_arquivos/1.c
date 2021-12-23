//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char Comida[50];
    double Peso;
    double Calorias;
} Dieta;

void lerArquivo (Dieta Alimentos [], char Nome[], int *N, int *MaiorMedia);

int main (){
    char Nome[20];
    int STam, N;
    Dieta Alimentos[50];
    int MaiorMedia = 0;

    printf ("Digite o nome do arquivo: ");
    fgets (Nome, 20, stdin);
    STam = strlen (Nome) - 1;
    Nome [STam] = '\0';

    lerArquivo (Alimentos, Nome, &N, &MaiorMedia);

    printf ("\nAlimento\t\tcal/grama\n---------------------------------");
    for (int i = 0; i < N; i++){
        printf ("\n%s\t\t     %.2lf", Alimentos[i].Comida, Alimentos[i].Calorias/Alimentos[i].Peso);
	if (i == MaiorMedia) printf (" *");
    }
    printf ("\n");

}

void lerArquivo (Dieta Alimentos [], char Nome[], int *N, int *MaiorMedia){
    FILE *Arquivo = fopen (Nome, "r");

    if (fopen(Nome, "r") == 0){
        printf("Erro! Argumento inexistente ou arquivo não encontrado.\n");
        exit (1);
    }

    fscanf (Arquivo, "%d", &*N);

    for (int i = 0; i < *N; i++){
        fscanf (Arquivo, "%s %lf %lf", Alimentos[i].Comida, &Alimentos[i].Peso, &Alimentos[i].Calorias);
        if (Alimentos[i].Calorias/Alimentos[i].Peso > Alimentos[*MaiorMedia].Calorias/Alimentos[*MaiorMedia].Peso) *MaiorMedia = i;
    }
    fclose (Arquivo);
    
}
