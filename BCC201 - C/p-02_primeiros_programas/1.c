#include <stdio.h>
#include <math.h>

int main()
{

	int x1, x2, x3, y;
	printf("Digite os valores de x1, x2 e x3:\n");
	scanf("%d %d %d", &x1, &x2, &x3);

	y = pow((x1 + pow(x2, 2) + pow(x3, 2)), 2) + pow((x1 * x2 * x3), 2);

	printf("\nx1 = %d, x2 = %d, x3 = %d\ny = %d\n", x1, x2, x3, y);
	return 0;
}
