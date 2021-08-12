//Pedro Lucas Damasceno Silva
//Turma 41 - PLE

#include <stdio.h>
#include <math.h>

typedef struct {
    double real;
    double imaginario;
} Complexo;

Complexo somaComplexo (Complexo x, Complexo y);
Complexo subComplexo (Complexo x, Complexo y);
Complexo multComplexo (Complexo x, Complexo y);

int main (){
    Complexo x, y, R;
    char operacao, operacao2;

    printf ("Calculadora de números complexos!\n\nDigite os valores de a e b (x = a + bi): ");
    scanf ("%lf %lf", &x.real, &x.imaginario);
    printf ("Digite os valores de c e d (y = c + di): ");
    scanf ("%lf %lf", &y.real, &y.imaginario);
    printf ("Digite a operação (+, - ou *): ");
    scanf (" %c", &operacao);

    switch (operacao){
        case '+': R = somaComplexo (x, y);
        break;
        case '-': R = subComplexo (x, y);
        break;
        case '*': R = multComplexo (x, y);
        break;
    }

    if (R.imaginario > 0) operacao2 = '+';
    else if (R.imaginario < 0) operacao2 = '-';
    else if (R.imaginario = 0) operacao2 = ' ';
    printf ("Resultado: %.0lf %c ", R.real, operacao2);
    if (R.imaginario < -1 || R.imaginario > 1) printf ("%.0lf", fabs(R.imaginario));
    if (R.imaginario != 0) printf ("i");
    return 0;
}

Complexo somaComplexo (Complexo x, Complexo y){
    Complexo R;
    R.real = (x.real + y.real);
    R.imaginario = (x.imaginario + y.imaginario);
    return R;
}

Complexo subComplexo (Complexo x, Complexo y){
    Complexo R;
    R.real = (x.real + y.real);
    R.imaginario = (x.imaginario + y.imaginario);
    return R;
}

Complexo multComplexo (Complexo x, Complexo y){
    Complexo R;
    R.real = ((x.real * y.real) - (x.imaginario * y.imaginario));
    R.imaginario = ((x.real * y.imaginario) + (x.imaginario * y.real));
    return R;
}