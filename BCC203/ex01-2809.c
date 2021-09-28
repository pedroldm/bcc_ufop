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
    FILE *arquivo_conceitos;
    dados_Aluno aluno;
    char conceito;
    float nota_media;

    if ((arquivo_alunos = fopen("alunos.txt", "r")) == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    if ((arquivo_conceitos = fopen("conceitos.txt", "w")) == NULL){
        printf("Erro na criação do arquivo.\n");
        exit(1);
    }

    while (fscanf(arquivo_alunos, "%d %s %f %f %f %d", &aluno.matricula, aluno.nome, &aluno.notas[0], &aluno.notas[1], &aluno.notas[2], &aluno.faltas) != EOF){

        nota_media = (aluno.notas[0] + aluno.notas[1] + aluno.notas[2]) / 3;
        
        if (aluno.faltas > 18)
            conceito = 'F';
        else {
            if (nota_media < 6)
                conceito = 'R';
            else if (nota_media >= 6 && nota_media < 7.5)
                conceito = 'C';
            else if (nota_media >= 7.5 && nota_media < 9.0)
                conceito = 'B';
            else if (nota_media >= 9.0 && nota_media <=10)
                conceito = 'A';
        }

        fprintf(arquivo_conceitos, "%d %s %c\n", aluno.matricula, aluno.nome, conceito);
    }

    fclose(arquivo_alunos);
    fclose(arquivo_conceitos);

    return 0;        
}