#ifndef ordenacao_h
#define ordenacao_h

int *alocaVetor(int *vetor, int n);
int *desalocaVetor(int *vetor);
void particionarVetor(int *vetor, int margem_Esquerda, int n, int *movimentos);
void mergeSort(int *vetor, int margem_Esquerda, int nova_Margem, int n, int *movimentos);

#endif
