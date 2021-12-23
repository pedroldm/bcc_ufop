#include <stdio.h>

int main ()
{
	char X;
	printf("Insira uma letra: ");
	scanf("%c", &X);

	if ( 	X == 'A' || X == 'a' || X == 'E' || X == 'e' || X == 'I' || X == 'i' || X == 'O' || X == 'o' || X == 'U' || X == 'u' )
	{
		printf("A letra %c é uma vogal!", X);
	}
	else printf("A letra %c é uma consoante.", X);
	return 0;
}
