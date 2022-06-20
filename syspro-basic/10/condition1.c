#include <stdio.h>


int factorial(int);

int main() {
    int i;
    for (i=0; i<5;i++) {
        #ifdef DEBUG
        printf("factorial(%d) = ", i);
        #endif
        printf("%d\n", factorial(i));
    }
}


int factorial(int n) {
    if (n==0) { return 1; }
    else {
        return n*factorial(n-1);
    }
}