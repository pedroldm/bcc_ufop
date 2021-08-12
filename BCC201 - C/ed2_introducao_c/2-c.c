#include <stdio.h>
#include <math.h>

int main()
{
	double A, B, R;
	printf("Insira dois números reais A e B:\n");
	scanf("%lf %lf", &A, &B);

	R = pow(A, 2);

	printf("A² = %.1lf\n", R);
	return 0;
}
