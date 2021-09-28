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
    FILE *arquivo_alunos;
    FILE *arquivo_binario;
    dados_Aluno aluno;

    if ((arquivo_alunos = fopen("alunos.txt", "r")) == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    if ((arquivo_binario = fopen("alunos_binario.bin", "wb")) == NULL){
        printf("Erro na criação do arquivo.\n");
        exit(1);
    }

    while (fscanf(arquivo_alunos, "%d %s %f %f %f %d", &aluno.matricula, aluno.nome, &aluno.notas[0], &aluno.notas[1], &aluno.notas[2], &aluno.faltas) != EOF)
        fwrite(&aluno, sizeof(dados_Aluno), 1, arquivo_binario);

    fclose(arquivo_alunos);
    fclose(arquivo_binario);

    return 0;        
}