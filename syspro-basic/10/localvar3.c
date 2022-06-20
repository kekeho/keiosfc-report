#include <stdio.h>

void f1(int n) {
    register int sum=0;
    int a;
    sum = sum + n;
    printf("sum=%d\n", sum);
    printf("&a=%p\n", &a);
}


int main() {
    f1(1);
    f1(2);
    f1(4);
}
