#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

int main(int argc, char const *argv[]) {
    int i;
    long k;

    char input[MAXLINE];

    fgets(input, MAXLINE, stdin);
    i = strtol(input, NULL, 10);
    k = strtol(input, NULL, 10);

    printf("i=%d, k = %ld\n", i, k);
    return 0;
}
