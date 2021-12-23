//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>

int main (){
    char Nome[100], NomeInvertido[100];

    do {
        printf ("Digite uma palavra ou 'FIM' para sair: ");
        fgets (Nome, 100, stdin);

        int tam = strlen (Nome) - 1;
        Nome [tam] = '\0';

        for (int i = 0; i < tam; i++){
            NomeInvertido[i] = Nome[tam - 1 - i];
        }

        NomeInvertido[tam] = '\0';
    
        if (strcmp(Nome, NomeInvertido) == 0) printf ("%s é um palíndromo!\n", Nome);
        else if (strcmp (Nome, "FIM") != 0) printf ("%s não é um palindromo.\n", Nome);
    } while (strcmp (Nome, "FIM"));

    return 0;
}