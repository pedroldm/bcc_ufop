#include <stdio.h>
#include <math.h>

int main ()
{
	float N, I, D;
	printf("Insira um número: ");
	scanf ("%f", &N);

	I = floor(N);
	D = N - I;

	printf("\nParte Inteira = %.0f\nParte decimal = %f\n", I, D);
	return 0;
}
