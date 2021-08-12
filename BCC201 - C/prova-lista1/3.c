#include <stdio.h>
#include <math.h>

int main (){
    int A, B, R;
    
    printf ("Insira dois números: ");
    scanf ("%d %d", &A, &B);
    
    if (A > B) printf ("%lf - %lf", pow (B, 2), sqrt (A));
    if (B > A) printf ("%lf - %lf", pow (A, 2), sqrt (B));
    if (A == B) printf ("Números iguais.");
    return 0;
}