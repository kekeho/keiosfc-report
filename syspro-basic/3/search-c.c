#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 256


int searchc(char *s, char c) {
    // sが被検索文字列, cが検索文字
    char *p;
    int i = 1;

    // 順番に見ていく
    for (p = s; *p != '\0'; p++,i++) {
        if (*p == c) {
            break;
        }
    }

    if (*p == '\0') {
        return -1;
    } else {
        return i;
    }
}


int main() {
    char input[MAXLEN];
    int c, loc;

    printf("文字列を入れてください\n");
    fgets(input, MAXLEN, stdin);

    printf("探す文字を入れてください\n");
    c = getc(stdin);
    loc = searchc(input, c);

    if (loc < 0) {
        printf("%cは見つかりませんでした\n", c);
    } else {
        printf("%cは%d番目に見つかりました\n", c, loc);
    }
}
