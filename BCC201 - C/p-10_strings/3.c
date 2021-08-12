//Pedro Lucas Damasceno Silva - 20.1.4003
//Turma 41 - PLE

#include <stdio.h>
#include <string.h>

int main (){
    char Frase [200], FraseCensurada [200];
    
    printf ("Digite o texto para censurar:\n");
    fgets (Frase, 200, stdin);

    int tam = strlen (Frase);

    for (int i = 0; i <= tam; i++){
        switch (Frase[i]){
            case 'a': Frase[i] = '@';
            break;
            case 'e': Frase[i] = '_';
            break;
            case 'i': Frase[i] = "|";
            break;
            case 'o': Frase[i] = "0";
            break;
            case 'u': Frase[i] = '#';
            break;
            case 's': Frase[i] = '$';
        }
    }

    printf ("\n%s", Frase);
    return 0;
}