//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

int main (){
    int N = 1;

    while (N < 3 || N > 80){
        printf ("Insira N ( 2 < N < 80 ): ");
        scanf ("%d", &N);
        if (N < 3 || N > 80) printf ("Entrada inválida.\n");
    }

    long long int Fibonacci [N - 1];

    for (int i = 0; i < N; i++){
        if (i == 0 || i == 1){
        Fibonacci [i] = 1;
        }
        else {
        Fibonacci [i] = Fibonacci [i-2] + Fibonacci [i-1];
        }
        printf ("%lld ", Fibonacci [i]);
    }
    
    return 0;
}
