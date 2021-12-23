//Trabalho Prático - Resta Um
//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAB_HOR "\u2501" // ━ 
#define TAB_VER "\u2503" // ┃
#define TAB_TL  "\u250F" // ┏ 
#define TAB_TR  "\u2513" // ┓ 
#define TAB_BL  "\u2517" // ┗ 
#define TAB_BR  "\u251B" // ┛ 
#define ANSI_BOLD "\x1b[1m"
#define ANSI_RESET "\x1b[0m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RED "\x1b[31m"

typedef struct {
    char C[1];
    char A[2];
} PossiveisComandos;

int **novoTabuleiro (int *N, int *M);
int **gerarTabuleiroTradicional (int *N, int *M, int Dificuldade);
int **gerarTabuleiroQuadrado (int *N, int *M, int Dificuldade);
int **gerarTabuleiroLosangular (int *N, int *M, int Dificuldade);
int **gerarTabuleiroTriangular (int *N, int *M, int Dificuldade);
int **lerTabuleiro (FILE *Arquivo, int *N, int *M);
void imprimirTabuleiro (int **Matriz, int N, int M);
void imprimirIndice ();
int lerEntrada (char Comando[], char Argumento[]);
int validarArgumento (int **Matriz, char Comando[], char Argumento[], int *MovimentosPossiveis, int N, int M);
int executarComando (int **Matriz, char Comando[], char Argumento[], int N, int M, PossiveisComandos MV[], int *MovimentosPossiveis);
int verificarResultado (int **Matriz, int *MovimentosPossiveis, int N, int M);
void calcularMovimentos (int **Matriz, int *MovimentosPossiveis, int N, int M, PossiveisComandos MV[]);
//Alocação dinâmica - 
int **criarMatriz (int *N, int *M);
void liberarMatriz (int **Matriz, int N);

int main (int argc, char *argv[]){
    FILE *Arquivo;
    int **Matriz, N, M, VerificadorResultado = 0, MovimentosPossiveis, VerificadorEntrada, VerificadorComando, VerificadorComando2;
    char Comando[11], Argumento[51];
    PossiveisComandos MV[100];

    Arquivo = fopen (argv[1], "r");
    if (Arquivo == NULL){
        Matriz = novoTabuleiro (&N, &M); //Função responsável por criar um novo tabuleiro caso não seja passado argumento ou esse seja inválido.
        getchar();
    }
    else {
        printf ("\nTabuleiro encontrado!\n");
        Matriz = lerTabuleiro (Arquivo, &N, &M); // Função responsável por ler o arquivo passado como argumento, alocar uma matriz de tamanho suficiente e preenchê-la com os elementos do arquivo.
        fclose (Arquivo);
    } 

    calcularMovimentos (Matriz, &MovimentosPossiveis, N, M, MV); // Função responsável por calcular possíveis movimentos no tabuleiro/matriz e armazená-los para serem impressos caso solicitado pelo usuário.

    if (MovimentosPossiveis == 0) {
        printf (ANSI_COLOR_RED ANSI_BOLD"Erro:"ANSI_RESET" não há possibilidade de comandos para esse tabuleiro.\n");
        exit (0);
    }

    imprimirTabuleiro (Matriz, N, M);
    imprimirIndice ();

    do {  // Ordenamento da execução do jogo.
	    do {
	        do {
                do { 
                    VerificadorEntrada = lerEntrada (Comando, Argumento);
                } while (VerificadorEntrada == 0);
                VerificadorComando = validarArgumento (Matriz, Comando, Argumento, &MovimentosPossiveis, N, M);
            } while (VerificadorComando == 0);
            VerificadorComando2 = executarComando (Matriz, Comando, Argumento, N, M, MV, &MovimentosPossiveis);
	    } while (VerificadorComando2 == 0);
	    imprimirTabuleiro (Matriz, N, M);
        calcularMovimentos (Matriz, &MovimentosPossiveis, N, M, MV);
        VerificadorResultado = verificarResultado (Matriz, &MovimentosPossiveis, N, M);
    } while (VerificadorResultado == 0);

    if (VerificadorResultado == 1) printf(ANSI_COLOR_BLUE ANSI_BOLD"\n\nParabéns! Resta UM!\n\n"ANSI_RESET);
    else if (VerificadorResultado == 2) printf(ANSI_COLOR_RED ANSI_BOLD"\n\nInfelizmente"ANSI_RESET", não há mais nenhuma jogada possível para o tabuleiro atual. :(\n\n");

    liberarMatriz (Matriz, N);

    return 0;
}

int **lerTabuleiro (FILE *Arquivo, int *N, int *M){
    int **Matriz;
    
    fscanf (Arquivo, "%d", N);
    fscanf (Arquivo, "%d", M);

    Matriz = criarMatriz(N, M);

    for (int i = 0; i < *N; i++){
        for (int j = 0; j < *M; j++){
            fscanf (Arquivo, "%d", &Matriz[i][j]);
        }
    }

    return Matriz;
}

void imprimirTabuleiro (int **Matriz, int N, int M){
    char Letra;

    printf ("\n");
    printf (TAB_TL);

    for (int i = 0; i < (M * 3) + 3; i++) printf (TAB_HOR);
	
    printf (TAB_TR"\n"TAB_VER);
    printf ("    ");

    for (Letra = 65; Letra < (M + 65); Letra++){
	    if (Letra != (M+65) - 1) printf(ANSI_BOLD ANSI_COLOR_BLUE"%c  "ANSI_RESET, Letra);
	    else printf(ANSI_BOLD ANSI_COLOR_BLUE "%c " ANSI_RESET, Letra);
    }

    printf (ANSI_RESET);
    printf(TAB_VER);
    printf ("\n");
    Letra = 65;

    for (int i = 0; i < N; i++){
        printf (TAB_VER ANSI_BOLD ANSI_COLOR_BLUE" %c  "ANSI_RESET, Letra);
        Letra++;

        for (int j = 0; j < M; j++){
	        if (j != M-1){
		        if (Matriz[i][j] == 0) printf (".  ");
                    else if (Matriz[i][j] == 1) printf ("O  ");
                    else if (Matriz[i][j] == -1) printf ("   ");
	        }
	        else {
                if (Matriz[i][j] == 0) printf (". ");
                else if (Matriz[i][j] == 1) printf ("O ");
                else if (Matriz[i][j] == -1) printf ("  ");
	        }
        }

	    printf (TAB_VER);
        printf ("\n");
    }

    printf(TAB_BL);

    for (int i = 0; i < (M * 3) + 3; i++) printf (TAB_HOR);

    printf(TAB_BR);
    printf("\n");
}

void imprimirIndice (){
    printf(ANSI_BOLD "\n\t- Instruções de comandos -\nComando\t\tArgumento\tResultado\n" ANSI_RESET);
    printf(ANSI_BOLD"c\t\t"ANSI_COLOR_BLUE"CD"ANSI_RESET"\t\tMove um pino na célula da linha C e coluna D para cima.\n"ANSI_BOLD"b\t\t"ANSI_COLOR_BLUE"CD"ANSI_RESET"\t\tMove um pino na célula da linha C e coluna D para baixo.\n"ANSI_BOLD"e\t\t"ANSI_COLOR_BLUE"CD"ANSI_RESET"\t\tMove um pino na célula da linha C e coluna D para a esquerda.\n"ANSI_BOLD"d\t\t"ANSI_COLOR_BLUE"CD"ANSI_RESET"\t\tMove um pino na célula da linha C e coluna D para a direita.\n");
    printf(""ANSI_BOLD"ajuda"ANSI_RESET"\t\tn\t\tSujestão de N possíveis movimentos.\n"ANSI_BOLD"salvar"ANSI_RESET"\t\tjogo\t\tSalva o jogo tal como está no arquivo 'jogo.txt'.\n"ANSI_BOLD"sair"ANSI_RESET"\t\t-\t\tEncerra o programa sem salvar as últimas alterações.\n"ANSI_BOLD"indice"ANSI_RESET"\t\t-\t\tImprime o índice de comandos/argumentos.\n"ANSI_BOLD"tabuleiro"ANSI_RESET"\t-\t\tImprime o tabuleiro atual.\n");
}

int lerEntrada (char Comando[], char Argumento[]){ //Validação do comando.
    int STam, CTam, ATam, Espaco = 0, j = 0;
    char String[60];

    for (int i = 0; i <= 50; i++){
	    Argumento[i] = '\0';
	    if (i < 11) Comando[i] = '\0';
    }
    
    printf ("\nComando: ");
    fgets (String, 60, stdin); //Optei pelo fgets por registrar até o enter. No caso do scanf, se o usuário inserisse várias strings, mensagens de erros seriam impressas repetidas vezes em vez de apenas uma.
    STam = strlen (String);
    String[STam - 1] = '\0';
    
    for (int i = 0; i < STam; i++){
        if (String[i] == ' '){
            Espaco++;
            i++;
        }

        if (Espaco == 0) Comando[i] = String[i];
        else {
            Argumento[j] = String[i];
            j++;
        }
    }

    CTam = strlen (Comando);
    ATam = strlen (Argumento);

    for (int i = 0; i < CTam; i++){
        if (Comando[i] >= 65 && Comando[i] <= 90) Comando[i] += 32; //Caso algum comando de movimento seja maiúsculo. (case insensitive)
    }

    if (strcmp (Comando, "c") == 0 || strcmp (Comando, "b") == 0 || strcmp (Comando, "d") == 0 || strcmp(Comando, "e") == 0){ //Caso algum argumento de movimento seja minúsculo. (case insensitive)
        for (int i = 0; i < ATam; i++){
            if (Argumento[i] >= 97 && Argumento[i] <= 122) Argumento[i] -= 32;
        }
    }

    if (strlen (Comando) > 10){
        printf (ANSI_COLOR_RED ANSI_BOLD"Comando inválido:"ANSI_RESET" o comando pode ter até 10 caracteres.");
        return 0;
    }

    if (strlen (Argumento) > 50){
        printf (ANSI_COLOR_RED ANSI_BOLD"Argumento inválido:"ANSI_RESET" o argumento pode ter até 50 caracteres.");
        return 0;
    }
    
    if (strcmp (Comando, "c") == 0 || strcmp (Comando, "b") == 0 || strcmp (Comando, "d") == 0 || strcmp(Comando, "e") == 0 || strcmp(Comando, "sair") == 0 || strcmp(Comando, "ajuda") == 0 || strcmp(Comando, "salvar") == 0 || strcmp(Comando, "indice") == 0 || strcmp(Comando, "tabuleiro") == 0) return 1;
    else{
        printf (ANSI_COLOR_RED ANSI_BOLD"Comando inválido!"ANSI_RESET" Reveja o índice de instruções do jogo.");
        return 0;
    }
}

int validarArgumento (int **Matriz, char Comando[], char Argumento[], int *MovimentosPossiveis, int N, int M){ //Validação do argumento.
    int X = Argumento[0] - 65;
    int Y = Argumento[1] - 65;
    int VerificadorA1 = 0, VerificadorA2 = 0,  VerificadorA3 = 0, VerificadorA4 = 0;

    if (strcmp(Comando, "c") == 0 || strcmp(Comando, "b") == 0 || strcmp(Comando, "e") == 0 || strcmp(Comando, "d") == 0){
        if ((Argumento[0] >= 65 && Argumento[0] <= 90) && (Argumento[1] >= 65 && Argumento[1] <= 90)) VerificadorA1 = 1; // Verificando se 'C' e 'D' pertencem ao intervalo de 65-90 da tabela ASCII (letras maiúsculas);
        else {
            printf (ANSI_COLOR_RED ANSI_BOLD"Argumento inválido:"ANSI_RESET" 'C' e 'D' devem ser letras do alfabeto!");
            return 0;
        }

        if (Argumento[0] - 65 >= N || Argumento[1] - 65 >= M){  // Verificando se 'C' e 'D' são colunas da matriz.
            printf (ANSI_COLOR_RED ANSI_BOLD"Argumento inválido:"ANSI_RESET" atente-se às margens do tabuleiro.");
            return 0;
        }

        if (strcmp (Comando, "c") == 0){
            if (Argumento[0] - 65 - 2 < 0){ // Evitando que haja vazamento de memória.
                printf (ANSI_COLOR_RED ANSI_BOLD"Argumento inválido:"ANSI_RESET" atente-se às margens do tabuleiro.");
                return 0;
            }
        }

        if (strcmp (Comando, "b") ==0){
            if (Argumento[0] - 65 + 2 >= N){
                printf (ANSI_COLOR_RED ANSI_BOLD"Argumento inválido:"ANSI_RESET" atente-se às margens do tabuleiro.");
                return 0;
            }
        }

        if (strcmp (Comando, "e") == 0){
            if (Argumento[1] - 65 - 2 < 0){
                printf (ANSI_COLOR_RED ANSI_BOLD"Argumento inválido:"ANSI_RESET" atente-se às margens do tabuleiro.");
                return 0;
            }
        }

        if (strcmp (Comando, "d") == 0){
            if (Argumento[1] - 65 + 2 >= M){
                printf (ANSI_COLOR_RED ANSI_BOLD"Argumento inválido:"ANSI_RESET" atente-se às margens do tabuleiro.");
                return 0;
            }
        }
    }

    if (strcmp(Comando, "ajuda") == 0){
       if (strlen(Argumento) == 1){
            if (Argumento[0] < 48 || Argumento[0] > 57){
                printf (ANSI_COLOR_RED ANSI_BOLD"Erro:"ANSI_RESET" apenas números podem ser passados como argumentos para esse comando.");
                return 0;
            }
            
            if (Argumento[0] == 48){ 
                printf (ANSI_COLOR_RED ANSI_BOLD"Erro:"ANSI_RESET" apenas números maiores que zero podem ser passados como argumentos para esse comando.");
                return 0;
            }
            if (Argumento[0] - 48 > *MovimentosPossiveis){ 
                printf (ANSI_COLOR_RED ANSI_BOLD"Erro:"ANSI_RESET" o número de jogadas requisitadas excede o de movimentos possíveis (%d)!", *MovimentosPossiveis);
                return 0;
            }
            if (Argumento[0] >= 49 && Argumento[0] <= 57 && Argumento[0] - 48 <= *MovimentosPossiveis) VerificadorA1 = 1, VerificadorA2 = 1, VerificadorA3 = 1, VerificadorA4 = 1;
       }

        if (strlen(Argumento) == 2){
           if (Argumento[0] < 48 || Argumento[0] > 57){
                printf (ANSI_COLOR_RED ANSI_BOLD"Erro:"ANSI_RESET" apenas números podem ser passados como argumentos para esse comando.");
                return 0;
           }
           if (Argumento[1] < 48 || Argumento[1] > 57){ 
                printf (ANSI_COLOR_RED ANSI_BOLD"Erro:"ANSI_RESET" apenas números podem ser passados como argumentos para esse comando.");
                return 0;
           }
           if (((Argumento[0] - 48) * 10) + (Argumento[1] - 48) > *MovimentosPossiveis){
                printf (ANSI_COLOR_RED ANSI_BOLD"Erro:"ANSI_RESET" o número de jogadas requisitadas excede o de movimentos possíveis (%d)!", *MovimentosPossiveis);
                return 0;
           }
           if (((Argumento[0] - 48) * 10) + (Argumento[1] - 48) <= *MovimentosPossiveis && Argumento[0] >= 49 && Argumento[0] <= 57 && Argumento[1] >= 48 && Argumento[1] <= 57) VerificadorA1 = 1, VerificadorA2 = 1, VerificadorA3 = 1, VerificadorA4 = 1;
        }

        if (strlen(Argumento) > 2){
            printf (ANSI_COLOR_RED ANSI_BOLD"Erro:"ANSI_RESET" o número de jogadas requisitadas não pode ser maior que 99.");
            return 0;
        }
    }

    if (strcmp(Comando, "salvar") == 0){
        if (strlen(Argumento) > 0) VerificadorA1 = 1, VerificadorA2 = 1, VerificadorA3 = 1, VerificadorA4 = 1; // Verificando se há um argumento para nomear o arquivo.
    }

    if (strcmp(Comando, "indice") == 0) VerificadorA1 = 1, VerificadorA2 = 1, VerificadorA3 = 1, VerificadorA4 = 1;

    if (strcmp(Comando, "sair") == 0) VerificadorA1 = 1, VerificadorA2 = 1, VerificadorA3 = 1, VerificadorA4 = 1;

    if (strcmp(Comando, "tabuleiro") == 0) VerificadorA1 = 1, VerificadorA2 = 1, VerificadorA3 = 1, VerificadorA4 = 1;

    if (strcmp(Comando, "c") == 0){ //Verificando se o movimento inserido está de acordo com a disposição das peças no tabuleiro atual.
        if (Matriz[X-1][Y] == 1 && X-1 >= 0) VerificadorA2 = 1;
        if (Matriz[X-2][Y] == 0 && X-2 >= 0) VerificadorA3 = 1;
        if (Matriz[X][Y] == 1) VerificadorA4 = 1;
    }

    if (strcmp(Comando, "b") == 0){
        if (Matriz[X+1][Y] == 1 && X+1 < N) VerificadorA2 = 1;
        if (Matriz[X+2][Y] == 0 && X+2 < N) VerificadorA3 = 1;
        if (Matriz[X][Y] == 1) VerificadorA4 = 1;
    }

    if (strcmp(Comando, "e") == 0){
        if (Matriz[X][Y-1] == 1 && Y-1 >= 0) VerificadorA2 = 1;
        if (Matriz[X][Y-2] == 0 && Y-2 >= 0) VerificadorA3 = 1;
        if (Matriz[X][Y] == 1) VerificadorA4 = 1;
    }

    if (strcmp(Comando, "d") == 0){
        if (Matriz[X][Y+1] == 1 && Y+1 < M) VerificadorA2 = 1;
        if (Matriz[X][Y+2] == 0 && Y+2 < M) VerificadorA3 = 1;
        if (Matriz[X][Y] == 1) VerificadorA4 = 1;
    }

    if (VerificadorA1 == 1 && VerificadorA2 == 1 && VerificadorA3 == 1 && VerificadorA4 == 1) return 1;
    else {
        printf (ANSI_COLOR_RED ANSI_BOLD"Comando inválido!"ANSI_RESET" Reveja as instruções e o tabuleiro!");
        return 0;
    }
}

int executarComando (int **Matriz, char Comando[], char Argumento[], int N, int M, PossiveisComandos MV[], int *MovimentosPossiveis){
    int X = Argumento[0] - 65;
    int Y = Argumento[1] - 65;
    FILE *SalvarArquivo;

    if (strcmp(Comando, "c") == 0){ //Executar a movimentação, caso válida, das peças.
        Matriz[X - 2][Y] = 1;
        Matriz[X - 1][Y] = 0;
        Matriz[X][Y] = 0;
    }

    if (strcmp(Comando, "b") == 0){
        Matriz[X + 2][Y] = 1;
        Matriz[X + 1][Y] = 0;
        Matriz[X][Y] = 0;
    }

    if (strcmp(Comando, "e") == 0){
        Matriz[X][Y - 2] = 1;
        Matriz[X][Y - 1] = 0;
        Matriz[X][Y] = 0;
    }

    if (strcmp(Comando, "d") == 0){
        Matriz[X][Y + 2] = 1;
        Matriz[X][Y + 1] = 0;
        Matriz[X][Y] = 0;
    }

    if (strcmp(Comando, "ajuda") == 0){
        int Request, MVA, i;
        srand (time(NULL));

        if (strlen (Argumento) == 1){
            Request = Argumento[0] - 48;
        }

        if (strlen(Argumento) == 2){ // Caso o argumento seja maior que 9.
            Request = (Argumento[0] - 48) * 10 + (Argumento[1] - 48);
        }

        for (i = 0; i < Request; i++){
            printf ("Entrei!\n Request = %d", Request);
            calcularMovimentos (Matriz, MovimentosPossiveis, N, M, MV);
            MVA = rand () % *MovimentosPossiveis;
            Comando[0] = MV[MVA].C[0];
            Argumento[0] = MV[MVA].A[0];
            Argumento[1] = MV[MVA].A[1];
            executarComando (Matriz, Comando, Argumento, N, M, MV, MovimentosPossiveis);
        }

        return 0;
    }

    if (strcmp(Comando, "salvar") == 0){
        SalvarArquivo = fopen (Argumento, "w");
        fprintf(SalvarArquivo, "%d %d\n\n", N, M);
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                fprintf (SalvarArquivo, "%2d ", Matriz[i][j]);
            }
            fprintf (SalvarArquivo, "\n");
        }
        printf ("Jogo salvo em '%s' !\n", Argumento);
	    fclose (SalvarArquivo);
	    return 0;	
    }

    if (strcmp(Comando, "sair") == 0){
        liberarMatriz (Matriz, N);
        printf("Obrigado por jogar! Até a próxima! :)\n");
        exit (0);
    }

    if (strcmp(Comando, "indice") == 0) {
	    imprimirIndice ();
	    return 0;
    }
 
    if (strcmp(Comando, "tabuleiro") == 0) {
        imprimirTabuleiro (Matriz, N, M);
        return 0;
    }

    return 1;
}

void calcularMovimentos (int **Matriz, int *MovimentosPossiveis, int N, int M, PossiveisComandos MV[]){
    int X = 0, i, j;
    char C, D;

    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
            if ( i >= 2 && Matriz[i][j] == 1 && Matriz[i-1][j] == 1 && Matriz[i-2][j] == 0){
                C = i + 65;
                D = j + 65;
                MV[X].C[0] = 'c';
                MV[X].A[0] = C;
                MV[X].A[1] = D;
                X++; //Mudar de struct caso um movimento possível seja identificado e registrado.
            }
            if ( i < N - 2 && Matriz[i][j] == 1 && Matriz[i+1][j] == 1 && Matriz[i+2][j] == 0){
                C = i + 65;
                D = j + 65;
                MV[X].C[0] = 'b';
                MV[X].A[0] = C;
                MV[X].A[1] = D;
                X++;//b CD
            }
            if ( j < M - 2 && Matriz[i][j] == 1 && Matriz[i][j+1] == 1 && Matriz[i][j+2] == 0){
                C = i + 65;
                D = j + 65;
                MV[X].C[0] = 'd';
                MV[X].A[0] = C;
                MV[X].A[1] = D;
                X++;//d CD
            }
            if ( j >= 2 && Matriz[i][j] == 1 && Matriz[i][j-1] == 1 && Matriz[i][j-2] == 0){
                C = i + 65;
                D = j + 65;
                MV[X].C[0] = 'e';
                MV[X].A[0] = C;
                MV[X].A[1] = D;
                X++;//e CD
            }
        }
    }

    *MovimentosPossiveis = X; //Ponteiro utilizado para conferir o desfecho e se há movimentos possíveis para a matriz de um arquivo passado por argumento.
}

int verificarResultado (int **Matriz, int *MovimentosPossiveis, int N, int M){
    int Pecas = 0;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (Matriz[i][j] == 1){
                Pecas++;
            }
        }
    }

    if (Pecas == 1 && *MovimentosPossiveis == 0) return 1; //Vitória! :D
    if (Pecas > 1 && *MovimentosPossiveis == 0) return 2; //Derrota... :(
    return 0; //Segue o jogo.
}

int **novoTabuleiro (int *N, int *M){
    int **Matriz;
    FILE *NovoTabuleiro;
    char Formato, Resp1;
    int A1, A2, V1, Dificuldade = 0;

    printf (ANSI_COLOR_RED ANSI_BOLD"Erro!"ANSI_RESET" Argumento inexistente ou arquivo não encontrado.\nGostaria de gerar um novo tabuleiro aleatório (S/N)? ");

    do {
        scanf ("%c", &Resp1);
	    if (Resp1 == 'S' || Resp1 == 's') V1 = 1;
	    else if (Resp1 == 'N' || Resp1 == 'n') V1 = 1;
	    if (V1 != 1) {
            printf (ANSI_COLOR_RED ANSI_BOLD"Comando inválido!"ANSI_RESET" Insira apenas 'S' ou 'N'.");
	        getchar ();
        }
    } while (V1 != 1);

    if (Resp1 == 'N' || Resp1 == 'n'){
        printf ("Ok! Até um outro dia!"); 
        exit (0);
    }

    if (Resp1 == 'S' || Resp1 == 's'){ //Sorteio do formato e dificuldade do tabuleiro aleatório.
        srand (time(NULL));
        A1 = rand () % 100;
        A2 = rand () % 3;
        if (A1 >= 0 && A1 <= 25) {
            Formato = 'T';
        }
        else if (A1 > 25 && A1 <= 50) {
            Formato = 'Q';
        }
        else if (A1 > 50 && A1 <= 75) {
            Formato = 'D';
        }
        else if (A1 > 75 && A1 <= 100) {
            Formato = 'L';
        }

        if (A2 == 0) Dificuldade = 1;
        else if (A2 == 1) Dificuldade = 2;
        else if (A2 == 2) Dificuldade = 3;
    }

    if (Formato == 'T') Matriz = gerarTabuleiroTradicional (N, M, Dificuldade); //Chamada da função mediante formato sorteado.
    else if (Formato == 'Q') Matriz = gerarTabuleiroQuadrado (N, M, Dificuldade);
    else if (Formato == 'L') Matriz = gerarTabuleiroLosangular (N, M, Dificuldade);
    else if (Formato == 'D') Matriz = gerarTabuleiroTriangular (N, M, Dificuldade);

    NovoTabuleiro = fopen ("novo_tabuleiro.txt", "w"); //Gerar um arquivo de texto contendo o novo jogo aleatório.
    fprintf(NovoTabuleiro, "%d %d\n\n", *N, *M);
    for (int i = 0; i < *N; i++){
        for (int j = 0; j < *M; j++){
            fprintf (NovoTabuleiro, "%2d ", Matriz[i][j]);
            }
        fprintf (NovoTabuleiro, "\n");
        }
    printf ("\nNovo tabuleiro salvo em 'novo_tabuleiro.txt'!\n");
    fclose (NovoTabuleiro);

    return Matriz;
}

int **gerarTabuleiroTradicional (int *N, int *M, int Dificuldade){
    int Impares[5] = {1, 3, 5, 7, 9};
    int **Matriz;

    if (Dificuldade == 1) {
        *N = 6 + Impares[rand () % 3]; //Matriz quadrada de lado 7 9 11 
        *M = *N;
    }

    if (Dificuldade == 2){
        *N = 10 + Impares[rand () % 3]; //Matriz quadrada de lado 11 13 ou 15
        *M = *N;
    }

    if (Dificuldade == 3){
        *N = 16 + Impares[rand () % 5]; //Matriz quadrada de lado 17 19 21 23 25
        *M = *N;
    }

    Matriz = criarMatriz(N, M); //Chamada da função que aloca memória para a matriz mediante suas dimensões.

    for (int i = 0; i < *N; i++){
        for (int j = 0; j < *M; j++){
            if (i == ceil (*N/2) || i == ceil (*N/2) - 1 || i == ceil (*N/2) + 1 || j == ceil (*N/2) || j == ceil (*N/2) - 1 || j == ceil (*N/2) + 1) Matriz[i][j] = 1;
            else Matriz[i][j] = -1;
        }
    }

    int Centroi = ceil (*N/2);
    int Centroj = ceil (*M/2);

    Matriz[Centroi][Centroj] = 0;

    return Matriz;
}

int **gerarTabuleiroQuadrado (int *N, int *M, int Dificuldade){
    int **Matriz;
    int Impares[5] = {1, 3, 5, 7, 9};

    if (Dificuldade == 1) {
        *N = 6 + Impares[rand () % 3];
        *M = *N;
    }

    if (Dificuldade == 2){
        *N = 10 + Impares[rand () % 3];
        *M = *N;
    }

    if (Dificuldade == 3){
        *N = 16 + Impares[rand () % 5];
        *M = *N;
    }

    Matriz = criarMatriz (N, M);
    
    for (int i = 0; i < *N; i++){
        for (int j = 0; j < *M; j++){
            if (i == floor (*M/2) && j == floor (*N/2))Matriz[i][j] = 0;
            else Matriz[i][j] = 1;
        }
    }

    return Matriz;
}

int **gerarTabuleiroTriangular (int *N, int *M, int Dificuldade){
    int **Matriz;
    int Impares[5] = {1, 3, 5, 7, 9};

    if (Dificuldade == 1) {
        *M = 6 + Impares[rand () % 3];
        *N = ceil (*M/2) + 1;
    }
    else if (Dificuldade == 2){
        *M = 10 + Impares[rand () % 3];
        *N = ceil (*M/2) + 1;
    }
    else if (Dificuldade == 3){
        *M = 16 + Impares[rand () % 5];
        *N = ceil (*M/2) + 1;
    }

    Matriz = criarMatriz (N, M);

    int D1 = ceil (*M/2);
    int D2 = D1;
    int Centroi = ceil (*N/2);
    int Centroj = ceil (*M/2);

    for (int i = 0; i < *N; i++){
        for (int j = 0; j < *M; j++){
            if (j < D1 || j > D2) Matriz[i][j] = -1;
            else Matriz[i][j] = 1;
        }
        D1--;
        D2++;
    }

    Matriz[Centroi][Centroj] = 0;

    return Matriz;
}

int **gerarTabuleiroLosangular (int *N, int *M, int Dificuldade){
    int **Matriz;
    int Impares[5] = {1, 3, 5, 7, 9};

    if (Dificuldade == 1) {
        *N = 6 + Impares[rand () % 3];
        *M = *N;
    }

    if (Dificuldade == 2){
        *N = 10 + Impares[rand () % 3];
        *M = *N;
    }

    if (Dificuldade == 3){
        *N = 16 + Impares[rand () % 5];
        *M = *N;
    }

    Matriz = criarMatriz (N, M);

    int D1 = ceil (*M/2);
    int D2 = D1;
    int Centroi = ceil (*N/2);
    int Centroj = ceil (*M/2);

    for (int i = 0; i < ceil (*M/2) + 1; i++){
        for (int j = 0; j < *M; j++){
            if (j < D1 || j > D2) Matriz[i][j] = -1;
            else Matriz[i][j] = 1;
        }
        D1--;
        D2++;
    }
   
    D1+=2;
    D2-=2;

    Matriz[Centroi][Centroj] = 0;

    for (int i = ceil (*M/2) + 1; i < *N; i++){
        for (int j = 0; j < *M; j++){
            if (j < D1 || j > D2) Matriz[i][j] = -1;
            else Matriz[i][j] = 1;
        }
        D1++;
        D2--;
    }

    return Matriz;
}

int **criarMatriz (int *N, int *M){
    int **Matriz;
    Matriz = malloc (*N * sizeof(int*));
    
    for (int i = 0; i < *N; i++){
        Matriz[i] = malloc (*M * sizeof(int));
    }

    return Matriz;
}

void liberarMatriz (int **Matriz, int N){
    for (int i = 0; i < N; i++){
        free (Matriz[i]);
    }
    
    free (Matriz);
}