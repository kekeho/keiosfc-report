#include <stdio.h>


void multi2(int *a, int *b) {
    *b = *a * 2;
    printf("In multi2: a=%d, b=%d\n", *a, *b);
    return;
}


int main(int argc, char const *argv[]) {
    int p = 0, q = 0;
    p = 10, q = 0;
    multi2(&p, &q);
    printf("In main: p=%d, q=%d\n", p, q);

    return 0;
}
