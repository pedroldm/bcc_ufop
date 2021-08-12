#include <stdio.h>

int main()
{
	double A, B, R;
	printf("Insira dois números reais A e B:\n");
	scanf("%lf %lf", &A, &B);

	R = A + B;

	printf("A + B = %.1lf\n", R);
	return 0;
}
