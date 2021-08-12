#include "maquina.h"

int main()
{
    blocoMemoria RAM[TAM_RAM];
    blocoMemoria cacheL1[TAM_CACHEL1];
    blocoMemoria cacheL2[TAM_CACHEL2];
    blocoMemoria cacheL3[TAM_CACHEL3];
    unidade_Instrucao vetorInstrucao[NRO_INSTRUCOES];
    int cache1_Hit = 0, cache2_Hit = 0, cache3_Hit = 0, cache1_Miss = 0, cache2_Miss = 0, cache3_Miss = 0, custoTotal = 0;

    iniciarMemoria(RAM, TAM_RAM, 0);
    iniciarMemoria(cacheL1, TAM_CACHEL1, 1);
    iniciarMemoria(cacheL2, TAM_CACHEL2, 1);
    iniciarMemoria(cacheL3, TAM_CACHEL3, 1);
    iniciarInstrucoes(vetorInstrucao);

    maquinaInterpretada(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao, &cache1_Hit, &cache2_Hit, &cache3_Hit, &cache1_Miss, &cache2_Miss, &cache3_Miss, &custoTotal);

    imprimirRelatorio(&cache1_Hit, &cache2_Hit, &cache3_Hit, &cache1_Miss, &cache2_Miss, &cache3_Miss, &custoTotal);

    return 0;
}