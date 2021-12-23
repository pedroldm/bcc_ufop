#include <stdio.h>
#include <string.h>

typedef struct {
    char Nome[70];
    double Altura;
    int Nascimento;
} DadosPessoais;

DadosPessoais novoCadastro();
void listarNomeAltura (DadosPessoais Dados[], int aux);
void listarNascimento (DadosPessoais Dados[], int aux);

int main (){
    DadosPessoais Dados[100];
    int aux = 0, opcao;

    do{
        printf ("Digite 1 para inserir uma nova pessoa\n       2 para listar nomes e alturas\n       3 para listar os nomes que nasceram depois de determinado ano\n       0 para sair\n");
        scanf ("%d", &opcao);
        
        switch (opcao){
            case 1: 
                Dados[aux] = novoCadastro();
                aux++;
                break;
            case 2:
                listarNomeAltura (Dados, aux);
                break;
            case 3:
                listarNascimento (Dados, aux);
                break;
        }

    } while (opcao != 0);
    return 0;
}

DadosPessoais novoCadastro(){
    DadosPessoais Dados;
    printf ("Insira o nome: ");
    scanf ("%s", Dados.Nome);
    printf ("Insira a altura: ");
    scanf ("%lf", &Dados.Altura);
    printf ("Insira a data de nascimento: ");
    scanf ("%d", &Dados.Nascimento);
    return Dados;
}

void listarNomeAltura (DadosPessoais Dados[], int aux){
    for (int i = 0; i < aux; i++){
        printf ("Nome: %s - Altura: %.2lf\n", Dados[i].Nome, Dados[i].Altura);
    }
}

void listarNascimento (DadosPessoais Dados[], int aux){
    int Ano;
    printf ("Insira o ano desejado: ");
    scanf ("%d", Ano);

    for (int i = 0; i < aux; i++){
        if (Dados[i].Nascimento >= Ano) printf ("Nome: %s\n", Dados[i].Nome);
    }
}