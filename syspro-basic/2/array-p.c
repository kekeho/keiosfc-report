#include <stdio.h>

#define MAXNUM 10


void array(int b[]) {
    int i;
    for (i=0; i < MAXNUM; i++) {
        b[i] *= 2;
    }

    return;
}


int main(int argc, char const *argv[]) {
    int i, a[MAXNUM];

    for (i = 0; i < MAXNUM; i++) {
        a[i] = i;
    }

    array(a); // aはポインタなので, 参照渡しに

    for (i = 0; i < MAXNUM; i++ ){
        printf("a(%d) = %d\n", i, a[i]);
    }

    return 0;
}
