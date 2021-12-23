#include <stdio.h>
#include <math.h>
#define G 9.807

int main()
{
	float T, V, S;
	printf("Insira o tempo (s): ");
	scanf("%f", &T);	

	if ( T >= 0 )
	{
		V = G * T;
		S = (G * pow(T, 2)) / 2;
		printf("Velocidade = %.2f m/s\nDistância total percorrida = %.2f metros\n", V, S);
	}
	else printf("O valor do tempo não pode ser negativo.\n");
	return 0;
}
