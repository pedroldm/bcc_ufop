#ifndef ordenacao_h
#define ordenacao_h

typedef struct
{
    char nome_Pais[50];
    int medalhas_Ouro;
    int medalhas_Prata;
    int medalhas_Bronze;
} medalhas_pais;

medalhas_pais *alocar_Vetor(medalhas_pais *vetor_Paises, int quantidade_Paises);
medalhas_pais *desalocar_Vetor(medalhas_pais *vetor_Paises);
void ler_Quantidade(int *quantidade_Paises);
void ler_Medalhas(medalhas_pais *vetor_Paises, int quantidade_Paises);
void selectionSort_Ouro(medalhas_pais *vetor_Paises, int quantidade_Paises);
void bubbleSort_Prata(medalhas_pais *vetor_Paises, int quantidade_Paises);
void bubbleSort_Bronze(medalhas_pais *vetor_Paises, int quantidade_Paises);
void bubbleSort_Alfabetica(medalhas_pais *vetor_Paises, int quantidade_Paises);
void imprimir_Quadro(medalhas_pais *vetor_Paises, int quantidade_Paises);

#endif