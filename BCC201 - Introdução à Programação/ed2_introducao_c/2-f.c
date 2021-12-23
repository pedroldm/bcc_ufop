#include <stdio.h>
#include <math.h>

int main ()
{
	double A, B, R;
	printf("Insira dois números reais A e B:\n");
	scanf("%lf %lf", &A, &B);

	R = fabs (A);

	printf("Módulo de A = %.1f\n", R);
	return 0;
}
