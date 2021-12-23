#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int matricula;
    char nome [50];
    float notas [3];
    int faltas;
} dados_Aluno;

int main (){
    FILE *binario_Original;
    FILE *binario_Temporario;
    int excluir_Matricula;
    dados_Aluno aluno;

    printf("Insira a matrícula a ser excluída:");
    scanf("%d", &excluir_Matricula);

    if ((binario_Original = fopen("alunos_binario.bin", "rb")) == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    if ((binario_Temporario = fopen("arquivo_temporario.bin", "w")) == NULL){
        printf("Erro na criação do arquivo.\n");
        exit(1);
    }

    while (fread(&aluno, sizeof(dados_Aluno), 1, binario_Original))
        if (aluno.matricula != excluir_Matricula)
            fwrite(&aluno, sizeof(dados_Aluno), 1, binario_Temporario);

    fclose(binario_Original);
    remove("binario_Original.bin");
    rename("binario_Temporario.bin", "binario_Original.bin");

    return 0;        
}