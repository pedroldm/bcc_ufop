#include <stdio.h>
#include <stdlib.h>

long long int fibLogN(int n);
void exponenciaMatriz(long long int M[2][2], int n);
void multiplicaMatriz(long long int M[2][2], long long int I[2][2]);

int main(int argc, char *argv[]) {
    (argc > 1) ? argc = atoi(argv[1]) : scanf("%d", &argc);
    printf("%llu\n", fibLogN(argc));
    return 0;
}

long long int fibLogN(int n) {
    long long int M[2][2] = {{1, 1}, {1, 0}};
    if (!n) return 0;
    exponenciaMatriz(M, n - 1);
    return M[0][0];
}

void exponenciaMatriz(long long int M[2][2], int n) {
    if (n <= 1) return;                                 
      
    exponenciaMatriz(M, n / 2);                         

    long long int R[2][2];
    R[0][0] = M[0][0] * M[0][0] + M[0][1] * M[1][0];
    R[0][1] = M[0][0] * M[0][1] + M[0][1] * M[1][1];
    R[1][0] = M[1][0] * M[0][0] + M[1][1] * M[1][0];
    R[1][1] = M[1][0] * M[0][1] + M[1][1] * M[1][1];
    M[0][0] = R[0][0];
    M[0][1] = R[0][1];
    M[1][0] = R[1][0];
    M[1][1] = R[1][1];

    if (n % 2 != 0) {
        long long int I[2][2] = {{1, 1}, {1, 0}};     
        long long int R[2][2];
        R[0][0] = M[0][0] * I[0][0] + M[0][1] * I[1][0];
        R[0][1] = M[0][0] * I[0][1] + M[0][1] * I[1][1];
        R[1][0] = M[1][0] * I[0][0] + M[1][1] * I[1][0];
        R[1][1] = M[1][0] * I[0][1] + M[1][1] * I[1][1];
        M[0][0] = R[0][0];
        M[0][1] = R[0][1];
        M[1][0] = R[1][0];
        M[1][1] = R[1][1];
    }
}

/* 
    O custo de todas as instruções é constante, com exceção da recursividade existente na função exponenciaMatriz.
    A condição de parada (linha 22), tem custo 1. Portanto, T(n) = 1, se n = 1.
    Para demais valores de n, temos o custo de cada linha:  22.    1
                                                            24.    T(n/2)
                                                            26.    1
                                                            27-30. 4
                                                            31-34. 1
                                                            36.    1
                                                            37-38. 2*
                                                            39-42. 4*
                                                            43-46. 1*
                                                            * As linhas 37-46 são executadas apenas n/2 vezes, haja vista a verificação de n % 2 == 0.
    T(n) = 1 + T(n/2) + 1 + 4*4 + 1 + 1 + (2*2 + 4*4 + 1*4)/2

    Portanto: T(n) = 1, se n = 1
              T(n) = T(n/2) + 28, se n > 1

    Iteração: T(n) = 28 + T(n/2)
              T(n) = 28 + (28 + T(n/4)) = 56 + T(n/2^2)
              T(n) = 56 + (28 + T(n/8)) = 84 + T(n/2^3)
              .
              .
              .
              T(2^k) = k x 28 + T(n/2^k) = log n x 28 + T(1)
              T(n) = Theta(n)
*/