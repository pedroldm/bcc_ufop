#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TipoAluno *alocaAlunos(TipoAluno *alunos, int n)
{
  alunos = (TipoAluno *)malloc(n * sizeof(TipoAluno));
  if (alunos == NULL)
  {
    printf("Memória insuficiente.\n");
    exit(1);
  }

  return alunos;
}

TipoAluno *desalocaAlunos(TipoAluno *alunos)
{
  free(alunos);

  return NULL;
}

void ordena(TipoAluno *alunos, int n)
{
  TipoAluno TAD_aux;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n - (i + 1); j++)
    {
      if (strcmp(alunos[j].nome, alunos[j + 1].nome) > 0)
      {
        TAD_aux = alunos[j];
        alunos[j] = alunos[j + 1];
        alunos[j + 1] = TAD_aux;
      }
    }
  }
}
