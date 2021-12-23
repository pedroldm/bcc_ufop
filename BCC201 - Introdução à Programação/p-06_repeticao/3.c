#include <stdio.h>
int main ()
{

	int a = 5, b = 3, c = 2, d;
	int *p = &d;

	if (a > b && b > c){
		*p = c;
		a = c;
		c = d;
		printf ("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
	}

	if (a >= d) printf ("*p+2=%d\n", *p+2);
	if (a < b && b < c) printf ("%d < %d < %d\n", a, b, c);

	return 0;
}