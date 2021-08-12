#include "prioridade.h"
#include <stdio.h>

int main()
{
	int n, m, tempo_Total = 0;
	TipoCaixa *heap = NULL;

	scanf("%d %d", &n, &m);
	heap = alocaVetor(heap, n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &heap[i].tempo_Atendimento);
		heap[i].nro_Identificacao = i + 1;
		heap[i].somar_Tempo = 0;
	}

	while (m--)
	{
		int nro_Produtos;
		scanf("%d", &nro_Produtos);
		Heap_Constroi(heap, n);
		heap[0].somar_Tempo += nro_Produtos * heap[0].tempo_Atendimento;
		if (heap[0].somar_Tempo > tempo_Total)
			tempo_Total = heap[0].somar_Tempo;
	}

	heap = desalocaVetor(heap);
	printf("%d", tempo_Total);
	return 0;
}