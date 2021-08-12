#include <stdio.h>

int main ()
{
	float K, M, X, A;
	printf("Insira a constante elástica da mola (k): ");
	scanf("%f", &K);
	printf("Insira a massa do corpo (kg): ");
	scanf("%f", &M);
	printf("Insira a extensão a partir da posição inicial (x): ");
	scanf("%f", &X);

	if ( K >= 0 && M >= 0 )
	{
		A = (K * X) / M;
		printf("\nAceleração do corpo = %.2f (m/s)\n", A);
	}
	else printf("\nA constante elástica e a massa do corpo não admitem valores negativos.\n");
	return 0;
}
