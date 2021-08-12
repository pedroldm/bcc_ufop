#include "pilha.h"
#include <stdio.h>
#include <string.h>

int main()
{
  Pilha pilha;
  char ch;
  Item item;

  Pilha_Inicia(&pilha);

  while (scanf("%c", &ch) != EOF)
  {
    item.c = ch;
    switch (ch)
    {
    case 40:
      Pilha_Push(&pilha, item);
      break;
    case 41:
      Pilha_Pop(&pilha, &item);
      break;
    }

    if (item.c != 40)
    {
      printf("incorreto\n");
      Pilha_Esvazia(&pilha);
      return 0;
    }
  }

  if (Pilha_EhVazia(&pilha))
    printf("correto\n");
  else
    printf("incorreto\n");

  Pilha_Esvazia(&pilha);

  return 0;
}