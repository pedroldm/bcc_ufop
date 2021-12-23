#include <stdio.h>

int main (){
    int N, Menor;
    int i = 5;

    while (i > 0){
        printf ("Insira um número inteiro (restam %d): ", i);
        scanf ("%d", &N);
        if (i == 5) Menor = N;
        if (Menor > N) Menor = N;
        i--;
    }

    printf ("Menor = %d", Menor);
    return 0;
}