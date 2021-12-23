#include <stdio.h>
#include <math.h>

int main()
{
	double A, B, R;
	printf("Insira dois números reais A e B:\n");
	scanf("%lf %lf", &A, &B);

	R = sin(A - B);

	printf("Seno de A - B = %.2lf\n", R);
	return 0;
}
