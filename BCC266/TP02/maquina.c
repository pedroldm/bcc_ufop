/* 
    Gabriel Catizani Faria Oliveira - 20.1.4004
    Pedro Lucas Damasceno Silva - 20.1.4003
    TP02 - BCC266 - UFOP
*/

#include "maquina.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void iniciarMemoria(blocoMemoria *Memoria, int tam_Memoria, int boolean_Cache)
{
    srand(time(NULL));

    for (int i = 0; i < tam_Memoria; i++)
    {
        for (int j = 0; j < NRO_PALAVRAS; j++)
        {
            Memoria[i].data[j] = rand() % RAND_MEMORIA;
        }

        if (boolean_Cache)
            Memoria[i].tag = -1;

        else
            Memoria[i].tag = i;
        Memoria[i].relevancia = 0;
        Memoria[i].atualizado = 0;
    }
}

void iniciarInstrucoes(unidade_Instrucao *Instrucoes)
{
    srand(time(NULL));

    for (int i = 0; i < 20; i++)
    {
        Instrucoes[i].opCode = rand() % NRO_OPERACOES;
        Instrucoes[i].addressOne = rand() % TAM_RAM;
        Instrucoes[i].addressTwo = rand() % TAM_RAM;
        Instrucoes[i].addressThree = rand() % TAM_RAM;
    }

    for (int i = 20; i < NRO_INSTRUCOES; i++)
    {
        if (rand() % 100 < REPETIR_INSTRUCAO)
        {
            Instrucoes[i] = Instrucoes[i - (1 + rand() % 15)];
        }
        else
        {
            Instrucoes[i].opCode = rand() % NRO_OPERACOES;
            Instrucoes[i].addressOne = rand() % TAM_RAM;
            Instrucoes[i].addressTwo = rand() % TAM_RAM;
            Instrucoes[i].addressThree = rand() % TAM_RAM;
        }
    }

    Instrucoes[NRO_INSTRUCOES].opCode = -1;
}

int calcularExchange(blocoMemoria *cacheL, int cache_TAM)
{
    blocoMemoria exchange;
    exchange.relevancia = 100000;
    exchange.tempo = 0;
    int endereco;

    for (int i = 0; i < cache_TAM; i++)
    {
        if (cacheL[i].tag == -1)
            return i;
    }

    for (int i = 0; i < cache_TAM; i++)
    {
        if (exchange.relevancia > cacheL[i].relevancia)
        {
            endereco = i;
            exchange = cacheL[i];
        }
        else if (exchange.relevancia == cacheL[i].relevancia && exchange.tempo < cacheL[i].tempo)
        {
            endereco = i;
            exchange = cacheL[i];
        }
    }

    return endereco;
}

void apagarBloco(blocoMemoria *cache, int endereco)
{
    cache[endereco].tag = -1;
}

blocoMemoria buscarMemoria(blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3, blocoMemoria *RAM, int memory_Adress, int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *address3_L1, int *custoTotal)
{
    int exchangeL1, exchangeL2, exchangeL3;
    for (int i = 0; i < TAM_CACHEL1; i++)
    {
        if (cacheL1[i].tag == memory_Adress)
        {
            *cache1_Hit += 1;
            *custoTotal += 10;
            cacheL1[i].relevancia += 10;
            *address3_L1 = i;
            return cacheL1[i];
        }
    }

    for (int i = 0; i < TAM_CACHEL2; i++)
    {
        if (cacheL2[i].tag == memory_Adress)
        {
            *cache1_Miss += 1;
            *cache2_Hit += 1;
            *custoTotal += 20;
            exchangeL1 = calcularExchange(cacheL1, TAM_CACHEL1);
            exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
            exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
            if (cacheL3[exchangeL3].atualizado)
                RAM[cacheL3[exchangeL3].tag] = cacheL3[exchangeL3];
            cacheL3[exchangeL3] = cacheL2[exchangeL2];
            cacheL2[exchangeL2] = cacheL1[exchangeL1];
            cacheL1[exchangeL1] = cacheL2[i];
            apagarBloco(cacheL2, i);
            *address3_L1 = exchangeL1;
            cacheL1[exchangeL1].relevancia += 10;
            return cacheL1[exchangeL1];
        }
    }

    for (int i = 0; i < TAM_CACHEL3; i++)
    {
        if (cacheL3[i].tag == memory_Adress)
        {
            *cache1_Miss += 1;
            *cache2_Miss += 1;
            *cache3_Hit += 1;
            *custoTotal += 30;
            exchangeL1 = calcularExchange(cacheL1, TAM_CACHEL1);
            exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
            exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
            if (cacheL3[exchangeL3].atualizado)
                RAM[cacheL3[exchangeL3].tag] = cacheL3[exchangeL3];
            cacheL3[exchangeL3] = cacheL2[exchangeL2];
            cacheL2[exchangeL2] = cacheL1[exchangeL1];
            exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
            exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
            if (cacheL3[exchangeL3].atualizado)
                RAM[cacheL3[exchangeL3].tag] = cacheL3[exchangeL3];
            cacheL3[exchangeL3] = cacheL2[exchangeL2];
            cacheL2[exchangeL2] = cacheL3[i];
            cacheL1[exchangeL1] = cacheL2[exchangeL2];
            apagarBloco(cacheL3, i);
            apagarBloco(cacheL2, exchangeL2);
            *address3_L1 = exchangeL1;
            cacheL1[exchangeL1].relevancia += 10;
            return cacheL1[exchangeL1];
        }
    }

    *cache1_Miss += 1;
    *cache2_Miss += 1;
    *cache3_Miss += 1;
    *custoTotal += 10000;
    exchangeL1 = calcularExchange(cacheL1, TAM_CACHEL1);
    exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
    exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
    if (cacheL3[exchangeL3].atualizado)
        RAM[cacheL3[exchangeL3].tag] = cacheL3[exchangeL3];
    cacheL3[exchangeL3] = cacheL2[exchangeL2];
    cacheL2[exchangeL2] = cacheL1[exchangeL1];
    exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
    exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
    if (cacheL3[exchangeL3].atualizado)
        RAM[cacheL3[exchangeL3].tag] = cacheL3[exchangeL3];
    cacheL3[exchangeL3] = cacheL2[exchangeL2];
    exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
    if (cacheL3[exchangeL3].atualizado)
        RAM[cacheL3[exchangeL3].tag] = cacheL3[exchangeL3];
    cacheL3[exchangeL3] = RAM[memory_Adress];
    cacheL2[exchangeL2] = cacheL3[exchangeL3];
    cacheL1[exchangeL1] = cacheL2[exchangeL2];
    apagarBloco(cacheL3, exchangeL3);
    apagarBloco(cacheL2, exchangeL2);
    *address3_L1 = exchangeL1;
    cacheL1[exchangeL1].relevancia += 10;
    return cacheL1[exchangeL1];
}

void incrementarTempoRelevancia(blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3)
{
    for (int i = 0; i < TAM_CACHEL1; i++)
    {
        cacheL1[i].tempo++;
        cacheL1[i].relevancia--;
    }

    for (int i = 0; i < TAM_CACHEL2; i++)
    {
        cacheL2[i].tempo++;
        cacheL2[i].relevancia--;
    }

    for (int i = 0; i < TAM_CACHEL3; i++)
    {
        cacheL3[i].tempo++;
        cacheL3[i].relevancia--;
    }
}

void varrerCache(blocoMemoria *RAM, blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3)
{
    for (int i = 0; i < TAM_CACHEL1; i++)
    {
        if (cacheL1[i].atualizado)
        {
            RAM[i] = cacheL1[i];
        }
    }

    for (int i = 0; i < TAM_CACHEL2; i++)
    {
        if (cacheL2[i].atualizado)
        {
            RAM[i] = cacheL2[i];
        }
    }

    for (int i = 0; i < TAM_CACHEL3; i++)
    {
        if (cacheL3[i].atualizado)
        {
            RAM[i] = cacheL3[i];
        }
    }
}

void maquinaInterpretada(blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3, blocoMemoria *RAM, unidade_Instrucao *vetorInstrucao, int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *custoTotal)
{
    blocoMemoria addressOne, addressTwo, addressThree;
    int address3_cacheL1;
    for (int i = 0; i < NRO_INSTRUCOES; i++)
    {
        switch (vetorInstrucao[i].opCode)
        {
        case -1:
            //Halt.
            varrerCache(RAM, cacheL1, cacheL2, cacheL3);
            return;
        case 0:
            // Soma.
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = somarInteiros(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;
        case 1:
            // Subtração.
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = subtrairInteiros(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;

        case 2:
            // Multiplicação a partir de somas sucessivas.
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = multiplicarInteiros(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;

        case 3:
            // Divisão a partir de subtrações sucessivas.
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = dividirInteiros(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;

        case 4:
            // Raiz quadrada por tentativas de multiplicação sucessivas.
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = sqrtInteiros(addressOne.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;

        case 5:
            // Pitágoras (sqrt(contentOne² + contentTwo²))
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = calcularPitagoras(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;

        case 6:
            // Área (contentOne x contentTwo).
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = calcularArea(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;

        case 7:
            // Fatorial de contentOne.
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = calcularFatorial(addressOne.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;

        case 8:
            // Exponencial por multiplicações (somas sucessivas) sucessivas.
            addressOne = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = calcularExponencial(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            break;
        }
    }
}

void imprimirRelatorio(int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *custoTotal)
{
    int int_Size = floor(log10(abs(*cache1_Hit + *cache2_Hit + *cache3_Hit))) + floor(log10(abs(*cache1_Hit))) + floor(log10(abs(*cache2_Hit))) + floor(log10(abs(*cache3_Hit))) + floor(log10(abs(*cache1_Miss + *cache2_Miss + *cache3_Miss))) + floor(log10(abs(*cache1_Miss))) + floor(log10(abs(*cache2_Miss))) + floor(log10(abs(*cache3_Miss))) + floor(log10(abs(*custoTotal))) + 9;

    printf(ANSI_BOLD "\n - Relatório - \n\n" ANSI_RESET);
    printf(TAB_TL);
    for (int i = 0; i < 67 + int_Size; i++)
        printf(TAB_HOR);
    printf(TAB_TR "\n");
    printf(TAB_VER);
    printf(ANSI_BOLD ANSI_COLOR_BLUE "  Cache Hit" ANSI_RESET " : " ANSI_BOLD "%d (%d / %d / %d)" ANSI_RESET " | " ANSI_COLOR_RED ANSI_BOLD "Cache Miss" ANSI_RESET " : " ANSI_BOLD "%d (%d / %d / %d)" ANSI_RESET " | " ANSI_BOLD ANSI_COLOR_YELLOW "Custo Total" ANSI_RESET " : " ANSI_BOLD "%d" ANSI_RESET "  " TAB_VER "\n", *cache1_Hit + *cache2_Hit + *cache3_Hit, *cache1_Hit, *cache2_Hit, *cache3_Hit, *cache1_Miss + *cache2_Miss + *cache3_Miss, *cache1_Miss, *cache2_Miss, *cache3_Miss, *custoTotal);
    printf(TAB_BL);
    for (int i = 0; i < 67 + int_Size; i++)
        printf(TAB_HOR);
    printf(TAB_BR "\n\n");
}

int somarInteiros(int contentOne, int contentTwo)
{
    printf(ANSI_BOLD ANSI_COLOR_RED "Soma" ANSI_RESET " %d + %d = %d\n", contentOne, contentTwo, contentOne + contentTwo);

    return contentOne + contentTwo;
}

int subtrairInteiros(int contentOne, int contentTwo)
{
    printf(ANSI_BOLD ANSI_COLOR_RED "Subtração" ANSI_RESET " %d - %d = %d\n", contentOne, contentTwo, contentOne - contentTwo);

    return contentOne - contentTwo;
}

int multiplicarInteiros(int contentOne, int contentTwo)
{
    int contentThree = 0;

    for (int j = 0; j < contentTwo; j++)
    {
        contentThree = somarInteiros(contentOne, contentThree);
        printf(ANSI_BOLD ANSI_COLOR_BLUE "(Multiplicação) " ANSI_RESET);
    }
    printf(ANSI_BOLD ANSI_COLOR_RED "Resultado : Multiplicação" ANSI_RESET " %d * %d = %d\n", contentOne, contentTwo, contentThree);

    return contentThree;
}

int dividirInteiros(int contentOne, int contentTwo)
{
    int contentThree = 0;

    while (contentOne > 0)
    {
        contentOne = subtrairInteiros(contentOne, contentTwo);
        contentThree = somarInteiros(contentThree, 1);
        printf(ANSI_BOLD ANSI_COLOR_BLUE "(Divisão) " ANSI_RESET);
    }

    if (contentOne < 0)
        contentThree = subtrairInteiros(contentThree, 1);

    printf(ANSI_BOLD ANSI_COLOR_RED "Resultado : Divisão" ANSI_RESET " %d / %d = %d\n", contentOne, contentTwo, contentThree);

    return contentThree;
}

int sqrtInteiros(int contentOne)
{
    int contentThree = 0;

    for (int j = 1; contentOne > 0; j += 2)
    {
        printf(ANSI_BOLD ANSI_COLOR_BLUE "(Sqrt) " ANSI_RESET);
        contentOne = subtrairInteiros(contentOne, j);
        printf(ANSI_BOLD ANSI_COLOR_BLUE "(Sqrt) " ANSI_RESET);
        contentThree = somarInteiros(contentThree, 1);
    }

    if (contentOne < 0)
        contentThree = subtrairInteiros(contentThree, 1);

    printf(ANSI_BOLD ANSI_COLOR_RED "Resultado : Sqrt" ANSI_RESET " %d = %d\n", contentOne, contentThree);

    return contentThree;
}

int calcularPitagoras(int contentOne, int contentTwo)
{
    int contentThree = 0;

    printf(ANSI_BOLD ANSI_COLOR_BLUE "(Pitágoras) " ANSI_RESET);
    contentThree = somarInteiros(multiplicarInteiros(contentOne, contentOne), contentThree);
    printf(ANSI_BOLD ANSI_COLOR_BLUE "(Pitágoras) " ANSI_RESET);
    contentThree = somarInteiros(multiplicarInteiros(contentTwo, contentTwo), contentThree);
    printf(ANSI_BOLD ANSI_COLOR_BLUE "(Pitágoras) " ANSI_RESET);
    contentThree = sqrtInteiros(contentThree);

    printf(ANSI_BOLD ANSI_COLOR_RED "Resultado : Pitágoras" ANSI_RESET " %d^2 + %d^2 = (sqrt) %d\n", contentOne, contentTwo, contentThree);

    return contentThree;
}

int calcularArea(int contentOne, int contentTwo)
{
    int contentThree = 0;

    printf(ANSI_BOLD ANSI_COLOR_BLUE "(Área) " ANSI_RESET);
    contentThree = multiplicarInteiros(contentOne, contentTwo);
    printf("Área de %d e %d: %d\n", contentOne, contentTwo, contentThree);

    return contentThree;
}

int calcularFatorial(int contentOne)
{
    int contentThree;

    for (contentThree = 1; contentOne > 1; contentOne = subtrairInteiros(contentOne, 1))
    {
        printf(ANSI_BOLD ANSI_COLOR_BLUE "(Fatorial) " ANSI_RESET);
        contentThree = multiplicarInteiros(contentThree, contentOne);
    }

    return contentThree;
}

int calcularExponencial(int contentOne, int contentTwo)
{
    int contentThree = contentOne;

    switch (contentTwo)
    {
    case 0:
        contentThree = 1;
        break;
    case 1:
        contentThree = contentOne;
        break;
    default:
        for (int i = 0; i < contentTwo - 1; i++)
        {
            printf(ANSI_BOLD ANSI_COLOR_BLUE "(Exponencial) " ANSI_RESET);
            contentOne = multiplicarInteiros(contentOne, contentThree);
        }
        contentThree = contentOne;
        break;
    }

    return contentThree;
}