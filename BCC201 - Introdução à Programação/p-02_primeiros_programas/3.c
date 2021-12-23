#include <stdio.h>

int main()
{
	float C, F, K;
	printf("Insira a temperatura em graus Celsius:");
	scanf("%f", &C);

	F = (C * 9) / 5 + 32;
	K = C + 273.15;

	printf("%.2f graus Celsius equivalem a:\n%.2f graus Fahrenheit\n%.2f graus Kelvin\n", C, F, K);
	return 0;
}
