//Alocação.
int *alocaVetor(int *v_Tiras, int n);
int *desalocaVetor(int *v_Tiras);
//Odenação.
void particionarVetor(int *vetor, int margem_Esquerda, int n);
void mergeSort(int *vetor, int margem_Esquerda, int nova_Margem, int n);
//Busca binária.
double calcularArea(int *v_Tiras, int n, double h);
double buscaBinaria(int *v_Tiras, int n, int a);