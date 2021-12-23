#include <stdio.h>

int main (){

    int num, *ptr, *ptr2;
    num = 7;
    ptr = &num;
    ptr2 = ptr;

    *ptr = 1;
    *ptr2 = 4;

    printf ("num = %d, ptr = %d, ptr2 = %d", num, *ptr, *ptr2);
    return 0;
}