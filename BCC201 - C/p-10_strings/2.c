//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>

int main (){
    char Nome[70], PNomes[70], UNome[70];

    printf ("Digite o nome completo: ");
    fgets (Nome, 70, stdin);

    int Espacos = 0, Letras = 0, tam = strlen (Nome), j = 0, x = 0, i;
    Nome [tam-1] = '\0';

    for (i = 0; i <= tam; i++){
        if (Nome[i] == ' ') Espacos++;
        if (Nome[i] != ' ' && Nome[i] != '\0')Letras++;
    }

    for (i = 0; i <= tam; i++){
        if (j != Espacos){
            if (Nome[i] == ' ') j++;
            PNomes[i] = Nome[i];
        }
        else if (j == Espacos){
            UNome[x] = Nome[i];
            x++;
        }
    }  

    int tam2 = strlen (UNome), tam3 = strlen (PNomes);
    PNomes [tam3 - 1] = '\0';

    printf ("%s, %s\nTotal de letras: %d\nTotal de letras do último sobrenome: %d", UNome, PNomes, Letras, tam2);
    return 0;
}