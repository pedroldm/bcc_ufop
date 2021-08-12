#include "ordenacao.h"
#include <stdio.h>

int main()
{

	int *vetor;
	int i, n, movimentos;
	while (scanf("%d", &n), n)
	{
		vetor = alocaVetor(vetor, n);
		for (i = 0; i < n; i++)
			scanf("%d", &vetor[i]);
		movimentos = 0;
		particionarVetor(vetor, 0, n - 1, &movimentos);
		if (movimentos % 2)
			printf("Marcelo\n");
		else
			printf("Carlos\n");
		vetor = desalocaVetor(vetor);
	}

	return 0;
}