#include "corretor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tentativa {
    char letra;
    int tempo;
    char julgamento[9];
};

void contarTentativas (int *n){
    scanf ("%d", n);
}

void lerTentativas (int n, TADtentativa* vetorTentativas){
    for (int i = 0; i < n; i++){
        scanf (" %c", &vetorTentativas[i].letra);
        scanf ("%d", &vetorTentativas[i].tempo);
        scanf (" %s", vetorTentativas[i].julgamento);
    }
}

int contabilizarAcertos (int n, TADtentativa* vetorTentativas){
    int s = 0;

    for (int i = 0; i < n; i++)
        if (strcmp(vetorTentativas[i].julgamento, "correto") == 0) s++; // Somar o número de tentativas corretas.

    return s;
}

int somarTempo (int n, TADtentativa* vetorTentativas){
    int p = 0;

    for (int i = 0; i < n; i++){
        if (strcmp(vetorTentativas[i].julgamento, "correto") == 0) p += vetorTentativas[i].tempo; // Somar o tempo de tentativas corretas.
        else{
            for (int j = i+1; j < n; j++) // Verificar se questões incorretas foram corrigidas e aplicar penalidade.
                if (vetorTentativas[j].letra == vetorTentativas[i].letra && (strcmp(vetorTentativas[j].julgamento, "correto") == 0)) p += 20; 
        }
    }

    return p;
}

void printResultado (int s, int p){
    printf ("%d %d", s, p);
}

TADtentativa* alocarTADtentativa (int n, TADtentativa* vetorTentativas){
    vetorTentativas = (TADtentativa*) malloc (n * sizeof(TADtentativa));
    if (vetorTentativas == NULL){
        printf ("Memória insuficiente.\n");
        exit (1);
    }

    return vetorTentativas;
}

TADtentativa* desalocarTADtentativa (TADtentativa* vetorTentativas){
    free (vetorTentativas);

    return NULL;
}