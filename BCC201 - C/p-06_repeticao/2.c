//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

int ehPrimo (int n);

int main (){
    int N;

    printf ("Digite um número: ");
    scanf ("%d", &N);

    if (ehPrimo(N)){
        printf("%d é um número primo!", N);
    }
    else printf ("%d NÃO é um número primo!", N);
    return 0;
}

int ehPrimo (int N){
    int i;
    int Divisores = 0;
    i = N;
    if ( i > 0 ){
        while (i > 0){
            if ( N % i == 0 ){
                Divisores++;
            }
        i--;
        }
    }
    else while (i < 0){
            if ( N % i == 0 ){
                Divisores++;
            }
        i++;
    }
    if ( Divisores != 2 ) return 0;
    else return 1;
}