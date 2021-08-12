#include <stdio.h>
#include <math.h>
int main()
{

	float P, H, IMC;
	printf("Insira seu peso, em quilogramas, e sua altura, em metros:\n");
	scanf("%f %f", &P, &H);

	IMC = P / pow(H, 2);

	printf("Seu IMC é: %.2f\n", IMC);
	return 0;
}
