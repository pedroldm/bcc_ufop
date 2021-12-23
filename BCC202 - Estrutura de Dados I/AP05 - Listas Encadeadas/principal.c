#include "lista.h"
#include <stdio.h>
#include <string.h>

#define MAX_STR 1200

int main()
{
  TLista original, nova;
  TItem x;
  char str[MAX_STR], str2[MAX_STR], str3[20];
  char *token;

  TLista_Inicia(&original);
  TLista_Inicia(&nova);

  fgets(str, MAX_STR, stdin);
  str[strcspn(str, "\n")] = '\0';
  token = strtok(str, " ");

  while (token != NULL)
  {
    strcpy(x.nome_amigo, token);
    TLista_InsereFinal(&original, x);
    token = strtok(NULL, " ");
  }

  fgets(str2, MAX_STR, stdin);
  str2[strcspn(str2, "\n")] = '\0';
  token = strtok(str2, " ");

  while (token != NULL)
  {
    strcpy(x.nome_amigo, token);
    TLista_InsereFinal(&nova, x);
    token = strtok(NULL, " ");
  }

  scanf("%s", str3);

  if (strcmp(str3, "nao") == 0)
    TLista_append(&original, &nova);
  else
    TLista_include(&original, &nova, str3);

  TLista_Imprime(&original);

  TLista_Esvazia(&original);

  return 0;
}
