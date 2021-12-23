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

    if ((arquivo_binario = fopen("alunos_binario.bin", "rb")) == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    if ((arquivo_alunos = fopen("alunos_texto.txt", "w")) == NULL){
        printf("Erro na criação do arquivo.\n");
        exit(1);
    }

    while (fread(&aluno, sizeof(dados_Aluno), 1, arquivo_binario))
        fprintf(arquivo_alunos, "%d %s %f %f %f %d\n", aluno.matricula, aluno.nome, aluno.notas[0], aluno.notas[1], aluno.notas[2], aluno.faltas);

    fclose(arquivo_alunos);
    fclose(arquivo_binario);

    return 0;        
}