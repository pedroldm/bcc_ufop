#include <stdio.h>
#include <math.h>

int main()
{
	float A, B, R;
	printf("Insira dois números reais A e B:\n");
	scanf("%lf %lf", &A, &B);

	R = sqrt(pow (A,2) + pow(B,2));

	printf("√A²+B² = %.1lf\n", R);
	return 0;
}
