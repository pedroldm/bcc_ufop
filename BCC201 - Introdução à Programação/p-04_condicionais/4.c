// Pedro Lucas Damasceno Silva - 20.1.4003
// Turma 41 - PLE

#include <stdio.h>
#include <ctype.h>

int main (){

    char ECE, SE, ECS, SS, L;
    printf ("Digite o sexo: ");
    scanf ("%c", &SE);
    printf ("Digite a inicial do estado civil: ");
    scanf (" %c", &ECE);

    ECS = toupper ( ECE );
    SS = toupper ( SE );

    switch ( SS ) {
        case 'F': L = 'a';
        break;
        case 'M': L = 'o';
        break;
    }
    
    if (( ECS == 'C' || ECS == 'V' || ECS == 'D' || ECS == 'S' ) && ( SS == 'F' || SS == 'M' )) {
        switch ( ECS ) {
        case 'C': printf ("\nCasad%c.", L);
        break;
        case 'V': printf ("\nViúv%c.", L);
        break;
        case 'D': printf ("\nDivorciad%c.", L);
        break;
        case 'S': printf ("\nSolteir%c.", L);
        break; 
	}
    }
    else printf ("\nSexo e/ou estado civil inválido(s).");
    return 0;
}