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

void iniciarHD(FILE *HD)
{
    HD = fopen("novo_hd.dat", "wb");
    int data[NRO_PALAVRAS] = {rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000};
    int n_ZERO = 0;

    for (int i = 0; i < TAM_HD; i++)
    {
        fwrite(&i, sizeof(int), 1, HD);         
        fwrite(data, sizeof(int), NRO_PALAVRAS, HD); 
        fwrite(&n_ZERO, sizeof(int), 1, HD);         
        fwrite(&n_ZERO, sizeof(int), 1, HD);
        fwrite(&n_ZERO, sizeof(int), 1, HD);
    }

    fclose(HD);
}

void iniciarMemoria(blocoMemoria *Memoria, int tam_Memoria, int boolean_Cache)
{
    for (int i = 0; i < tam_Memoria; i++)
    {
        for (int j = 0; j < NRO_PALAVRAS; j++)
        {
            Memoria[i].data[j] = rand() % RAND_MEMORIA;
        }
        Memoria[i].tag = -1;
        Memoria[i].relevancia = 0;
        Memoria[i].atualizado = 0;
    }
}

void iniciarInstrucoes(unidade_Instrucao *Instrucoes)
{
    for (int i = 0; i < 20; i++)
    {
        Instrucoes[i].opCode = rand() % NRO_OPERACOES;
        Instrucoes[i].addressOne = rand() % TAM_HD;
        Instrucoes[i].addressTwo = rand() % TAM_HD;
        Instrucoes[i].addressThree = rand() % TAM_HD;
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
            Instrucoes[i].addressOne = rand() % TAM_HD;
            Instrucoes[i].addressTwo = rand() % TAM_HD;
            Instrucoes[i].addressThree = rand() % TAM_HD;
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

blocoMemoria buscarHD(FILE *HD, int endereco_Bloco)
{
    blocoMemoria bloco;

    fseek(HD, sizeof(int) * (endereco_Bloco * 8), SEEK_SET);
    fread(&bloco.tag, sizeof(int), 1, HD);
    fread(&bloco.data[0], sizeof(int), 1, HD);
    fread(&bloco.data[1], sizeof(int), 1, HD);
    fread(&bloco.data[2], sizeof(int), 1, HD);
    fread(&bloco.data[3], sizeof(int), 1, HD);
    fread(&bloco.atualizado, sizeof(int), 1, HD);
    fread(&bloco.relevancia, sizeof(int), 1, HD);
    fread(&bloco.tempo, sizeof(int), 1, HD);

    rewind(HD);

    return bloco;
}

void escreverHD(FILE *HD, blocoMemoria bloco)
{
    bloco.atualizado = 0;
    bloco.relevancia = 0;
    bloco.tempo = 0;

    fseek(HD, sizeof(int) * (bloco.tag * 8), SEEK_SET);
    fwrite(&bloco.tag, sizeof(int), 1, HD);
    fwrite(&bloco.data[0], sizeof(int), 1, HD);
    fwrite(&bloco.data[1], sizeof(int), 1, HD);
    fwrite(&bloco.data[2], sizeof(int), 1, HD);
    fwrite(&bloco.data[3], sizeof(int), 1, HD);
    fwrite(&bloco.atualizado, sizeof(int), 1, HD);
    fwrite(&bloco.relevancia, sizeof(int), 1, HD);
    fwrite(&bloco.tempo, sizeof(int), 1, HD);

    rewind(HD);
}

blocoMemoria buscarMemoria(FILE *HD, blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3, blocoMemoria *RAM, int memory_Adress, int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *ram_Miss, int *address3_L1, int *custoTotal)
{
    int exchangeL1, exchangeL2, exchangeL3, exchangeRAM;
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

    for (int i = 0; i < TAM_RAM; i++)
    {
        if (RAM[i].tag == memory_Adress)
        {
            *cache1_Miss += 1;
            *cache2_Miss += 1;
            *cache3_Miss += 1;
            *custoTotal += 1000;
            exchangeL1 = calcularExchange(cacheL1, TAM_CACHEL1);
            exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
            exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
            if (cacheL3[exchangeL3].atualizado)
            {
                exchangeRAM = calcularExchange(RAM, TAM_RAM);
                if (RAM[exchangeRAM].atualizado)
                    escreverHD(HD, RAM[exchangeRAM]);
                RAM[exchangeRAM] = cacheL3[exchangeL3];
            }
            cacheL3[exchangeL3] = cacheL2[exchangeL2];
            cacheL2[exchangeL2] = cacheL1[exchangeL1];
            exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
            exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
            if (cacheL3[exchangeL3].atualizado)
            {
                exchangeRAM = calcularExchange(RAM, TAM_RAM);
                if (RAM[exchangeRAM].atualizado)
                    escreverHD(HD, RAM[exchangeRAM]);
                RAM[exchangeRAM] = cacheL3[exchangeL3];
            }
            cacheL3[exchangeL3] = cacheL2[exchangeL2];
            exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
            if (cacheL3[exchangeL3].atualizado)
            {
                exchangeRAM = calcularExchange(RAM, TAM_RAM);
                if (RAM[exchangeRAM].atualizado)
                    escreverHD(HD, RAM[exchangeRAM]);
                RAM[exchangeRAM] = cacheL3[exchangeL3];
            }
            cacheL3[exchangeL3] = RAM[i];
            cacheL2[exchangeL2] = cacheL3[exchangeL3];
            cacheL1[exchangeL1] = cacheL2[exchangeL2];
            apagarBloco(cacheL3, exchangeL3);
            apagarBloco(cacheL2, exchangeL2);
            *address3_L1 = exchangeL1;
            cacheL1[exchangeL1].relevancia += 10;
            return cacheL1[exchangeL1];
        }
    }

    *cache1_Miss += 1;
    *cache2_Miss += 1;
    *cache3_Miss += 1;
    *ram_Miss += 1;
    *custoTotal += 10000;
    exchangeL1 = calcularExchange(cacheL1, TAM_CACHEL1);
    exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
    exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
    exchangeRAM = calcularExchange(RAM, TAM_RAM);
    if (RAM[exchangeRAM].atualizado)
        escreverHD(HD, RAM[exchangeRAM]);
    RAM[exchangeRAM] = cacheL3[exchangeL3];
    cacheL3[exchangeL3] = cacheL2[exchangeL2];
    cacheL2[exchangeL2] = cacheL1[exchangeL1];
    exchangeL2 = calcularExchange(cacheL2, TAM_CACHEL2);
    exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
    exchangeRAM = calcularExchange(RAM, TAM_RAM);
    if (RAM[exchangeRAM].atualizado)
        escreverHD(HD, RAM[exchangeRAM]);
    RAM[exchangeRAM] = cacheL3[exchangeL3];
    cacheL3[exchangeL3] = cacheL2[exchangeL2];
    exchangeL3 = calcularExchange(cacheL3, TAM_CACHEL3);
    exchangeRAM = calcularExchange(RAM, TAM_RAM);
    if (RAM[exchangeRAM].atualizado)
        escreverHD(HD, RAM[exchangeRAM]);
    RAM[exchangeRAM] = cacheL3[exchangeL3];
    exchangeRAM = calcularExchange(RAM, TAM_RAM);
    if (RAM[exchangeRAM].atualizado)
        escreverHD(HD, RAM[exchangeRAM]);
    RAM[exchangeRAM] = buscarHD(HD, memory_Adress);
    cacheL3[exchangeL3] = RAM[exchangeRAM];
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

void tratadorInterrupcao(FILE *HD, blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3, blocoMemoria *RAM, int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *ram_Miss, int *custoTotal, int *n_Interrupcoes, int *instr_Interrupcoes)
{
    int nro_Interrupcoes = 1 + rand() % 9;
    *instr_Interrupcoes += nro_Interrupcoes;
    *n_Interrupcoes += 1;
    unidade_Instrucao *interrupcaoInstrucao = (unidade_Instrucao *)malloc((nro_Interrupcoes + 1) * sizeof(unidade_Instrucao));

    for (int i = 0; i < nro_Interrupcoes; i++)
    {
        interrupcaoInstrucao[i].opCode = rand() % NRO_OPERACOES;
        interrupcaoInstrucao[i].addressOne = rand() % TAM_RAM;
        interrupcaoInstrucao[i].addressTwo = rand() % TAM_RAM;
        interrupcaoInstrucao[i].addressThree = rand() % TAM_RAM;
    }

    printf(" - INTERUPÇÃO! - \n");
    maquinaInterpretada(HD, cacheL1, cacheL2, cacheL3, RAM, interrupcaoInstrucao, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, custoTotal, nro_Interrupcoes, ram_Miss, n_Interrupcoes, instr_Interrupcoes);
    printf(" - RESUMO DO PROGRAMA - \n");
}

void maquinaInterpretada(FILE *HD, blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3, blocoMemoria *RAM, unidade_Instrucao *vetorInstrucao, int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *custoTotal, int numero_Instrucoes, int *ram_Miss, int *nro_Interrupcoes, int *instr_Interrupcoes)
{
    blocoMemoria addressOne, addressTwo, addressThree;
    int address3_cacheL1;
    for (int i = 0; i < numero_Instrucoes; i++)
    {
        switch (vetorInstrucao[i].opCode)
        {
        case -1:
            //Halt.
            varrerCache(RAM, cacheL1, cacheL2, cacheL3);
            return;
        case 0:
            // Soma.
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = somarInteiros(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;
        case 1:
            // Subtração.
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = subtrairInteiros(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;

        case 2:
            // Multiplicação a partir de somas sucessivas.
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = multiplicarInteiros(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;

        case 3:
            // Divisão a partir de subtrações sucessivas.
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = dividirInteiros(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;

        case 4:
            // Raiz quadrada por tentativas de multiplicação sucessivas.
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = sqrtInteiros(addressOne.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;

        case 5:
            // Pitágoras (sqrt(contentOne² + contentTwo²))
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = calcularPitagoras(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;

        case 6:
            // Área (contentOne x contentTwo).
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = calcularArea(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;

        case 7:
            // Fatorial de contentOne.
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = calcularFatorial(addressOne.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;

        case 8:
            // Exponencial por multiplicações (somas sucessivas) sucessivas.
            addressOne = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressOne, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressTwo = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressTwo, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree = buscarMemoria(HD, cacheL1, cacheL2, cacheL3, RAM, vetorInstrucao[i].addressThree, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, &address3_cacheL1, custoTotal);
            incrementarTempoRelevancia(cacheL1, cacheL2, cacheL3);
            addressThree.data[rand() % NRO_PALAVRAS] = calcularExponencial(addressOne.data[rand() % NRO_PALAVRAS], addressTwo.data[rand() % NRO_PALAVRAS]);
            addressThree.tag = vetorInstrucao[i].addressThree;
            cacheL1[address3_cacheL1] = addressThree;
            cacheL1[address3_cacheL1].atualizado = 1;
            if (rand() % 100 < CHANCE_INTERRUPCAO)
                tratadorInterrupcao(HD, cacheL1, cacheL2, cacheL3, RAM, cache1_Hit, cache2_Hit, cache3_Hit, cache1_Miss, cache2_Miss, cache3_Miss, ram_Miss, custoTotal, nro_Interrupcoes, instr_Interrupcoes);
            break;
        }
    }
}

void imprimirRelatorio(int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *custoTotal, int *nro_Interrupcoes, int *instr_Interrupcoes, int *ram_Miss)
{
    printf(ANSI_BOLD "\n - Relatório - \n\n" ANSI_RESET);
    printf(ANSI_BOLD ANSI_COLOR_BLUE "Cache Hit" ANSI_RESET " : %d (%d / %d / %d)\n", *cache1_Hit + *cache2_Hit + *cache3_Hit, *cache1_Hit, *cache2_Hit, *cache3_Hit);
    printf(ANSI_BOLD ANSI_COLOR_RED "Cache Miss" ANSI_RESET " : %d (%d / %d / %d)\n", *cache1_Miss + *cache2_Miss + *cache3_Miss, *cache1_Miss, *cache2_Miss, *cache3_Miss);
    printf(ANSI_BOLD ANSI_COLOR_RED "RAM Miss" ANSI_RESET " : %d\n", *ram_Miss);
    printf("" ANSI_BOLD ANSI_COLOR_YELLOW "Interrupções" ANSI_RESET " : %d (%d)\n", *nro_Interrupcoes, *instr_Interrupcoes);
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "Custo total" ANSI_RESET " : %d", *custoTotal);
    printf("\n\n");
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