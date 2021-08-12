#include <stdio.h>
#include <ctype.h>

int main (){
    char A;
    scanf ("%c", &A);

    if (islower(A)) printf ("Minúsculo.");
    else if (isupper(A)) printf ("Maiúsculo. ");
    else printf ("Não.");

    return 0;
}