#include <stdio.h>


int main(int argc, char const *argv[]) {
    int x, y; int *p;

    p = &x;
    x = 7;
    y = *p;  // yにpの実体の値を代入

    printf("x = %d, y = %d\n", x, y); // 7, 7

    *p = 3;  // pの実体(x)に3を代入
    printf("x = %d, y = %d\n", x, y); // 3, 7
    printf("*p = %d\n", *p);

    return 0;
}
