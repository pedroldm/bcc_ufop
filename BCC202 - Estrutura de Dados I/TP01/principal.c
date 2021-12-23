/*
Pedro Lucas Damasceno Silva - 20.1.4003
BCC202 - P
Trabalho Prático 01
*/

#include "corretor.h"
#include <stdio.h>

int main () {
    TADtentativa* vetorTentativas = NULL;
    int n, s, p;

    contarTentativas (&n);
    vetorTentativas = alocarTADtentativa (n, vetorTentativas);
    lerTentativas (n, vetorTentativas);
    s = contabilizarAcertos(n, vetorTentativas);
    p = somarTempo (n, vetorTentativas);
    printResultado (s, p);
    vetorTentativas = desalocarTADtentativa (vetorTentativas);

    return 0;
}