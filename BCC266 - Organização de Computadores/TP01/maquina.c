/* Pedro Lucas Damasceno - 20.1.4003
   TP01 - BCC266 - UFOP
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANSI_BOLD "\x1b[1m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_RESET "\x1b[0m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define TAB_HOR "\u2501" // ━ 
#define TAB_VER "\u2503" // ┃
#define TAB_TL  "\u250F" // ┏ 
#define TAB_TR  "\u2513" // ┓ 
#define TAB_BL  "\u2517" // ┗ 
#define TAB_BR  "\u251B" // ┛ 

#define nroColunas 7
#define nroLinhas 20
#define nroOperacoes 7 // 9.

void preencherRAM (int **matrizRAM){ // Preenchimento das colunas de conteúdos da RAM com números aleatórios (lixo de memória).
    srand(time(NULL));

    int enderecoMemoria = 1;

    for (int i = 0; i <= nroLinhas; i++){
        matrizRAM[i][0] = 1 + rand () % nroOperacoes; // Vetor "vertical" de instruções.
        for (int j = 1; j < 4; j++){ 
            matrizRAM[i][j] = rand () % 1000;
            matrizRAM[i][j+3] = enderecoMemoria;
            enderecoMemoria++;
        }
    }

    matrizRAM[nroLinhas][0] = -1; //Halt.

    printf("Valores e opcodes sorteados!\n");
}

int somarInteiros (int contentOne, int contentTwo){
    printf (ANSI_BOLD ANSI_COLOR_RED"Soma"ANSI_RESET" %d + %d = %d\n", contentTwo, contentOne, contentOne + contentTwo);

    return contentOne + contentTwo;
}

int subtrairInteiros (int contentOne, int contentTwo){
    printf (ANSI_BOLD ANSI_COLOR_RED"Subtração"ANSI_RESET" %d - %d = %d\n", contentOne, contentTwo, contentOne - contentTwo);

    return contentOne - contentTwo;
}

int multiplicarInteiros (int contentOne, int contentTwo){
    int contentThree = 0;

    for (int j = 0; j < contentTwo; j++){
        contentThree = somarInteiros (contentOne, contentThree);
        printf (ANSI_BOLD ANSI_COLOR_BLUE"(Multiplicação) "ANSI_RESET);
    }
    printf (ANSI_BOLD ANSI_COLOR_RED"Resultado : Multiplicação"ANSI_RESET" %d * %d = %d\n", contentOne, contentTwo, contentThree);

    return contentThree;
}

int dividirInteiros (int contentOne, int contentTwo){
    int contentThree = 0;

    while (contentOne > 0){
        contentOne = subtrairInteiros (contentOne, contentTwo);
        contentThree = somarInteiros (contentThree, 1);
        printf (ANSI_BOLD ANSI_COLOR_BLUE"(Divisão) "ANSI_RESET);
    }

    if (contentOne < 0) contentThree = subtrairInteiros (contentThree, 1);

    printf (ANSI_BOLD ANSI_COLOR_RED"Resultado : Divisão"ANSI_RESET" %d / %d = %d\n", contentOne, contentTwo, contentThree);

    return contentThree;
}

int sqrtInteiros (int contentOne){
    int contentThree = 0;

    for (int j = 1; contentOne > 0; j+=2){
        printf (ANSI_BOLD ANSI_COLOR_BLUE"(Sqrt) "ANSI_RESET);
        contentOne = subtrairInteiros (contentOne, j);
        printf (ANSI_BOLD ANSI_COLOR_BLUE"(Sqrt) "ANSI_RESET);
        contentThree = somarInteiros (contentThree, 1);
    }

    if (contentOne < 0) contentThree = subtrairInteiros (contentThree, 1);

    printf (ANSI_BOLD ANSI_COLOR_RED"Resultado : Sqrt"ANSI_RESET" %d = %d\n", contentOne, contentThree);

    return contentThree;
}

int calcularPitagoras (int contentOne, int contentTwo){
    int contentThree = 0;

    printf (ANSI_BOLD ANSI_COLOR_BLUE"(Pitágoras) "ANSI_RESET);
    contentThree = somarInteiros (multiplicarInteiros (contentOne, contentOne), contentThree);
    printf (ANSI_BOLD ANSI_COLOR_BLUE"(Pitágoras) "ANSI_RESET);
    contentThree = somarInteiros (multiplicarInteiros (contentTwo, contentTwo), contentThree);
    printf (ANSI_BOLD ANSI_COLOR_BLUE"(Pitágoras) "ANSI_RESET);
    contentThree = sqrtInteiros (contentThree);

    printf (ANSI_BOLD ANSI_COLOR_RED"Resultado : Pitágoras"ANSI_RESET" %d^2 + %d^2 = (sqrt) %d\n", contentOne, contentTwo, contentThree);

    return contentThree;
}

int calcularArea (int contentOne, int contentTwo){
    int contentThree = 0;

    printf (ANSI_BOLD ANSI_COLOR_BLUE"(Área) "ANSI_RESET);
    contentThree = multiplicarInteiros (contentOne, contentTwo);
    printf ("Área de %d e %d: %d\n", contentOne, contentTwo, contentThree);

    return contentThree;
}

int calcularFatorial (int contentOne){ 
    int contentThree;

    for(contentThree = 1; contentOne > 1; contentOne = subtrairInteiros(contentOne, 1)){
        printf (ANSI_BOLD ANSI_COLOR_BLUE"(Fatorial) "ANSI_RESET);
        contentThree = multiplicarInteiros (contentThree, contentOne);
    }

    return contentThree;
}

int calcularExponencial (int contentOne, int contentTwo){
    int contentThree = contentOne;

    switch (contentTwo){
        case 0 : contentThree = 1;
        case 1 : contentThree = contentOne;
        default : { 
                for (int i = 0; i < contentTwo - 1; i++){
                printf (ANSI_BOLD ANSI_COLOR_BLUE"(Exponencial) "ANSI_RESET);
                contentOne = multiplicarInteiros (contentOne, contentThree);
                }
                contentThree = contentOne;
        }
    }

    return contentThree;
}

void maquinaInterpretada (int **matrizRAM){
    for(int i = 0; i <= nroLinhas; i++){
        switch (matrizRAM[i][0]){
            case -1 : { // Halt.
                return;
            }
            case 1 : { // Soma.
                matrizRAM[i][3] = somarInteiros (matrizRAM[i][1], matrizRAM[i][2]);
                break;
            }
            case 2 : { // Subtração.
                matrizRAM[i][3] = subtrairInteiros (matrizRAM[i][1], matrizRAM[i][2]);
                break;
            }
            case 3 : { // Multiplicação a partir de somas sucessivas.
                matrizRAM[i][3] = multiplicarInteiros (matrizRAM[i][1], matrizRAM[i][2]);
                break;
            }
            case 4 : { // Divisão a partir de subtrações sucessivas.
                matrizRAM[i][3] = dividirInteiros (matrizRAM[i][1], matrizRAM[i][2]);
                break;
            }
            case 5 : { // Raiz quadrada por tentativas de multiplicação sucessivas.
                matrizRAM[i][3] = sqrtInteiros (matrizRAM[i][1]); 
                break;
            }
            case 6 : { // Pitágoras (sqrt(contentOne² + contentTwo²))
                matrizRAM[i][3] = calcularPitagoras (matrizRAM[i][1], matrizRAM[i][2]);
                break;
            }
            case 7 : { // Área (contentOne x contentTwo).
                matrizRAM[i][3] = calcularArea (matrizRAM[i][1], matrizRAM[i][2]);
                break;
            }
            case 8 : { // Fatorial de contentOne.
                matrizRAM[i][3] = calcularFatorial (matrizRAM[i][1]);
                break;
            }
            case 9 : { // Exponencial por multiplicações (somas sucessivas) sucessivas.
                matrizRAM[i][3] = calcularExponencial (matrizRAM[i][1], matrizRAM[i][2]);
                break;
            }
        }
    }
    printf ("\n");
}

void printMatriz (int **matrizRAM){
    printf ("\n\n"ANSI_BOLD ANSI_COLOR_BLUE"          OPCODE       CONTENT ONE     CONTENT TWO     CONTENT THREE       ADDRESS ONE      ADDRESS TWO      ADDRESS THREE"ANSI_RESET"\n");
    printf ("\n"TAB_TL);

    for (int i = 0; i < 124; i++) printf (TAB_HOR);
    printf (TAB_TR"\n");
    
    for (int i = 0; i <= nroLinhas; i++){
        printf (TAB_VER);
        for (int j = 0; j < nroColunas; j++){
            printf ("%12d     ", matrizRAM[i][j]);
        }
        printf ("     "TAB_VER"\n");
    }

    printf (TAB_BL);
    for (int i = 0; i < 124; i++) printf (TAB_HOR);
    printf (TAB_BR"\n\n");
}

void printMenu (void){
    printf ("\n"ANSI_BOLD ANSI_COLOR_BLUE"- Menu -"ANSI_RESET"\n\n"ANSI_BOLD"1"ANSI_RESET". Exibir memória\n"ANSI_BOLD"2"ANSI_RESET". Exibir menu\n"ANSI_BOLD"3"ANSI_RESET". Sortear valores e opcodes\n"ANSI_BOLD"4"ANSI_RESET". Alterar memória\n"ANSI_BOLD"5"ANSI_RESET". Alterar opcode\n"ANSI_BOLD"6"ANSI_RESET". Efetuar operações\n"ANSI_BOLD"-1"ANSI_RESET". Sair\n\n");
}

int lerComando (void){                                                                 
    int opUsuario;
    printf ("Insira o comando: ");
    scanf ("%d", &opUsuario);

    return opUsuario;                                                                                                       
}

void alterarRAM (int **matrizRAM){ // Alterar conteúdos na memória a partir do endereço de memória.
    int enderecoMemoria, nLinha, nColuna, verifEndereco = 0;
    int novoValor;

    do {
        printf ("Insira o endereço de memória a ser alterado: ");
        scanf ("%d", &enderecoMemoria);
        
        for (int i = 0; i < nroLinhas; i++){
            for (int j = 4; j < nroColunas; j++){
                if (matrizRAM[i][j] == enderecoMemoria){ 
                    verifEndereco = 1;
                    nLinha = i;
                    nColuna = j-3;
                }
            }
        }

        if (verifEndereco == 0) printf (ANSI_BOLD ANSI_COLOR_RED"Endereço não encontrado!"ANSI_RESET" Consulte novamente a memória.\n");
    } while (verifEndereco == 0);

    printf ("Insira o valor a ser inserido: ");
    scanf ("%d", &novoValor);

    matrizRAM[nLinha][nColuna] = novoValor;
    printf ("Valor alterado com sucesso!\n");
}

void alterarOpcode (int **matrizRAM){
    int linhaOpcode;

    do {
        printf ("Insira a linha do opcode a ser alterado: ");
        scanf ("%d", &linhaOpcode);
        if (linhaOpcode < 0 || linhaOpcode > nroLinhas) printf (ANSI_BOLD ANSI_COLOR_RED"Linha inválida!"ANSI_RESET" Atente-se às margens da memória.\n");
    } while (linhaOpcode < 0 || linhaOpcode > nroLinhas);

    printf ("Insira o novo opcode: ");
    scanf ("%d", &matrizRAM[linhaOpcode-1][0]);
}

void ordenamentoExecucao (int **matrizRAM){ // Ordenamento da execução do programa (menu de opções).
    int intHalt = 0;

    printMatriz (matrizRAM);
    printMenu ();
    
    do {
        intHalt = lerComando ();
        switch (intHalt){
            case -1 : {
                exit(0);
            }
            case 1 : {
                printMatriz (matrizRAM);
                break;
            }
            case 2 : {
                printMenu ();
                break;
            }
            case 3 : {
                preencherRAM (matrizRAM);
                break;
            }
            case 4 : {
                alterarRAM (matrizRAM);
                break;
            }
            case 5 : {
                alterarOpcode (matrizRAM);
                break;
            }
            case 6 : {
                maquinaInterpretada (matrizRAM);
                break;
            }
            default : printf (ANSI_BOLD ANSI_COLOR_RED"Comando inválido!"ANSI_RESET" Insira apenas -1, 1, 2, 3, 4, 5 ou 6.\n");
        }
    } while (intHalt != -1); //Halt.
}

int **alocaMatriz(int **matrizRAM){
    matrizRAM = (int**) malloc (nroLinhas * sizeof(int*));
    if (matrizRAM == NULL){
        printf ("Memória insuficiente.\n");
        exit (1);
    }
    
    for (int i = 0; i <= nroLinhas; i++){
        matrizRAM[i] = (int*) malloc (nroColunas * sizeof(int));
        if (matrizRAM == NULL){
            printf ("Memória insuficiente.\n");
            exit (1);
        }
    }

    return matrizRAM;
}

int **desalocaMatriz(int **matrizRAM){
    for (int i = 0; i < nroColunas; i++){
        free (matrizRAM[i]);
    }
    free (matrizRAM);

    return NULL;
}