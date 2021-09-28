#include <stdio.h>
#ifndef maquina_h
#define maquina_h

#define REPETIR_INSTRUCAO 75
#define CHANCE_INTERRUPCAO 5

#define TAM_RAM 1000
#define TAM_HD 100000
#define TAM_CACHEL1 16
#define TAM_CACHEL2 32
#define TAM_CACHEL3 64
#define NRO_INSTRUCOES 10000
#define NRO_OPERACOES 2
#define RAND_MEMORIA 1000
#define NRO_PALAVRAS 4

#define ANSI_BOLD "\x1b[1m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\e[0;33m"
#define ANSI_RESET "\x1b[0m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define TAB_HOR "\u2501" // ━
#define TAB_VER "\u2503" // ┃
#define TAB_TL "\u250F"  // ┏
#define TAB_TR "\u2513"  // ┓
#define TAB_BL "\u2517"  // ┗
#define TAB_BR "\u251B"  // ┛

typedef struct
{
    int opCode;
    int addressOne;
    int addressTwo;
    int addressThree;
} unidade_Instrucao;

typedef struct
{
    int tag;
    int data[NRO_PALAVRAS];
    int atualizado;
    int relevancia;
    int tempo;
} blocoMemoria;

void iniciarHD(FILE *HD);
void tratadorInterrupcao(FILE *HD, blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3, blocoMemoria *RAM, int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *ram_Miss, int *custoTotal, int *n_Interrupcoes, int *instr_Interrupcoes);
blocoMemoria buscarHD(FILE *HD, int endereco_Bloco);
void escreverHD(FILE *HD, blocoMemoria bloco);

void iniciarMemoria(blocoMemoria *Memoria, int tam_Memoria, int boolean_Cache);
void iniciarInstrucoes(unidade_Instrucao *Instrucoes);
blocoMemoria buscarMemoria(FILE *HD, blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3, blocoMemoria *RAM, int memory_Adress, int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *ram_Miss, int *address3_L1, int *custoTotal);
int calcularExchange(blocoMemoria *cacheL, int cache_TAM);
void apagarBloco(blocoMemoria *cacheL, int posicao_Cache);
void maquinaInterpretada(FILE *HD, blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3, blocoMemoria *RAM, unidade_Instrucao *vetorInstrucao, int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *custoTotal, int numero_Instrucoes, int *ram_Miss, int *nro_Interrupcoes, int *instr_Interrupcoes);
void imprimirRelatorio(int *cache1_Hit, int *cache2_Hit, int *cache3_Hit, int *cache1_Miss, int *cache2_Miss, int *cache3_Miss, int *custoTotal, int *nro_Interrupcoes, int *instr_Interrupcoes, int *ram_Miss);
void varrerCache(blocoMemoria *RAM, blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3);
void incrementarTempoRelevancia(blocoMemoria *cacheL1, blocoMemoria *cacheL2, blocoMemoria *cacheL3);

int somarInteiros(int contentOne, int contentTwo);
int subtrairInteiros(int contentOne, int contentTwo);
int multiplicarInteiros(int contentOne, int contentTwo);
int dividirInteiros(int contentOne, int contentTwo);
int sqrtInteiros(int contentOne);
int calcularPitagoras(int contentOne, int contentTwo);
int calcularArea(int contentOne, int contentTwo);
int calcularFatorial(int contentOne);
int calcularExponencial(int contentOne, int contentTwo);

#endif
