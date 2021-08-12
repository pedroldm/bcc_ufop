//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

int main (){
    int X, Y;
    int Linha = 1;
    int Coluna = 1;
    int Verifica = 0;
    int DiagX;
    int DiagY;

    while (!Verifica){
        printf ("Movimentos de um Bispo no xadrez!\nDigite a linha em que o Bispo se encontra: ");
        scanf ("%d", &X);
        printf ("Digite a coluna em que o Bispo se encontra: ");
        scanf ("%d", &Y);
        
        if (X < 1 || X > 8 || Y < 1 || Y > 8){
            printf ("\nPosições inválidas.\n\n");
        }
        else{
            Verifica = 1;
        }
    }

    DiagX = X + Y;
    DiagY = X - Y;

    printf ("\nMovimentos possíveis:\n\n");
    printf("      1  2  3  4  5  6  7  8 \n");
    printf("    -------------------------\n");
    while (8 >= Linha){
        printf(" %d |", Linha);
        while   (8 >= Coluna){
            if ( (DiagX == Linha + Coluna) || (DiagY == Linha - Coluna) ) {
                printf ("  X");
            }
            else { 
                printf ("  -");
            }
            Coluna++;
        }
        printf ("\n");
        Linha++;
        Coluna = 1;
        }
    return 0;
}
