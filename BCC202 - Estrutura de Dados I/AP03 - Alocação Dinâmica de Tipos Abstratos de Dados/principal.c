/*
Pedro Lucas Damasceno Silva - 20.1.4003
BCC202 - P
Aula Prática 3 - Alocação Dinãmica de Tipos Abstratos de Dados
*/

#include "duende.h"
#include<stdio.h>

int main()
{
    int qtd;
    TADduende *D = NULL;
    TADtime *T = NULL;

    lerQuantidade(&qtd);
    D = alocaDuendes(D, qtd);
    T = alocaTimes(T, qtd);
    lerDuendes(D, qtd);
    escalarTimes(D, T, qtd);
    printTimes(T, qtd);
    D = desalocaDuendes(D);
    T = desalocaTimes(T);

    return 0;
}
