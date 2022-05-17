#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#define MAXLEN 512


int main() {
    FILE *fp;
    char input[MAXLEN];
    fp = fopen("hellotext", "r");

    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    fgets(input, MAXLEN, fp);  // fgets: 一行だけ読み込む.
    fclose(fp);
    printf("%s", input);
    exit(0);
}
