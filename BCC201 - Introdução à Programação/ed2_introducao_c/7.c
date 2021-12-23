#include <stdio.h>

int main()
{
	float R1, R2, RT;
	printf("Insira o valor dos resistores:");
	scanf("%f %f", &R1, &R2);	
	
	if ( R1 >= 0 && R2 >= 0 )
	{	
		RT = (R1 * R2) / (R1 + R2);
		printf("Associação em paralelo: %.2f Ohms\n", RT);
	}
	else printf("Os valores das resistências devem ser positivos.\n");
	return 0;
}
