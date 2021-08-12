#include "duende.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct duende {
  char nome[19];
  int idade;
  int escalado;
};

struct time {
  char lider[19];
  char entregador[19];
  char piloto[19];
  int idadeLider;
  int idadeEntregador;
  int idadePiloto;
};

void lerQuantidade(int *qtd){
  scanf ("%d", qtd);
}

TADduende *alocaDuendes(TADduende *D, int qtd){
  D = (TADduende*) malloc (qtd * sizeof(TADduende));
  if (D == NULL){
    printf ("Memória insuficiente.\n");
    exit (1);
  }

  return D;
}

TADtime *alocaTimes(TADtime *T, int qtd){
  T = (TADtime*) malloc ((qtd/3) * sizeof(TADtime));
  if (T == NULL){
    printf ("Memória insuficiente.\n");
    exit (1);
  }

  return T;
}

TADduende *desalocaDuendes(TADduende *D){
  free (D);

  return NULL;
}

TADtime *desalocaTimes(TADtime *T){
  free (T);

  return NULL;
}

void lerDuendes(TADduende *D, int qtd){
  int i;
  
  for (i = 0; i < qtd; i++){
    scanf (" %s", D[i].nome);
    scanf ("%d", &D[i].idade);
    D[i].escalado = 0;
  }
}

void escalarTimes(TADduende *D, TADtime *T, int qtd){
  int i, indice;

  for (i=0; i<(qtd/3); i++){
    indice = proximoMaisVelho(D, qtd);
    strcpy(T[i].lider, D[indice].nome);
    T[i].idadeLider = D[indice].idade;
    D[indice].escalado = 1;
  }

  for (i=0; i<(qtd/3); i++){
    indice = proximoMaisVelho(D, qtd);
    strcpy(T[i].entregador, D[indice].nome);
    T[i].idadeEntregador = D[indice].idade;
    D[indice].escalado = 1;
  }

  for (i=0; i<(qtd/3); i++){
    indice = proximoMaisVelho(D, qtd);
    strcpy(T[i].piloto, D[indice].nome);
    T[i].idadePiloto = D[indice].idade;
    D[indice].escalado = 1;
  }
}

int proximoMaisVelho(TADduende *D, int qtd){
  int indice, maiorIdade = 0;

  for (int i = 0; i < qtd; i++)
    if ((D[i].escalado == 0) && (D[i].idade > maiorIdade)){
        maiorIdade = D[i].idade;
        indice = i;
    } 

  return indice;
}

void printTimes(TADtime *T, int qtd){
  for (int i = 0; i < (qtd/3); i++){
    printf ("Time %d\n%s %d\n%s %d\n%s %d\n\n", i+1, T[i].lider, T[i].idadeLider, T[i].entregador, T[i].idadeEntregador, T[i].piloto, T[i].idadePiloto);
  }
}