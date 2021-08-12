//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>

void toUpper (char *Frase);

int main (){
    char Frase [200];
    
    printf ("Digite o texto: \n");
    fgets (Frase, 200, stdin);

    toUpper (Frase);

    printf ("%s", Frase);
    return 0;
}

void toUpper (char *Frase){
    int tam = strlen (Frase) - 1;
    Frase [tam] = '\0';
    
    for (int i = 0; i < tam; i++){
        if (Frase[i] >= 'a' && Frase[i] <= 'z') {
            Frase[i] -= 32;
        }
    }
}