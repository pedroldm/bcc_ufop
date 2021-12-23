//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>

typedef struct {
    int numerador;
    int denominador;
} Racional;

int equal (Racional algarismos[]);

int main (){
    Racional algarismos[2];
    double Verificador;

    for (int i = 0; i < 2; i++){
        printf ("Digite numerador e denominador de r%d: ", i+1);
        scanf ("%d %d", &algarismos[i].numerador, &algarismos[i].denominador);
    }

    Verificador = equal (algarismos);

    if (Verificador == 1) printf ("r1 e r2 são iguais!");
    else printf ("r1 e r2 são diferentes.");

    return 0;
}

int equal (Racional algarismos[]){
   
    int MDC[2];
    double Resultados[2];

    for (int i = 0; i < 2; i++){
        int A = algarismos[i].numerador;
        int B = algarismos[i].denominador;
        int Resto = algarismos[i].numerador % algarismos[i].denominador;
        while (Resto != 0){
            algarismos[i].numerador = algarismos[i].denominador;
            algarismos[i].denominador = Resto;
            Resto = algarismos[i].numerador % algarismos[i].denominador;
        }
        MDC[i] = algarismos[i].denominador;
        algarismos[i].numerador = A / MDC[i];
        algarismos[i].denominador = B / MDC[i];
        Resultados[i] = algarismos[i].numerador / algarismos[i].denominador;
    }

    if (Resultados[0] == Resultados[1]) return 1;
    else return 0;
}
