/**
 * Copyright (c) 2022 Hiroki Takemura (kekeho)
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 256

int main() {
    char str1[MAXLINE];
    char *s;

    printf("文字列を入れてください\n");
    fgets(str1, MAXLINE, stdin);

    s = strchr(str1, '\n');
    if (s != NULL) { *s = '\0'; }

    printf("入力されたのは%sです\n", str1);

    for (s = str1; *s != '\0'; s++) {
        if (isdigit(*s)) {
            printf("%cは数字です\n", *s);
            continue;
        }

        if (isalpha(*s)) {
            printf("%cはAlphabetです\n", *s);
            continue;
        }

        if (isspace(*s)) {
            printf("%cは空白文字です\n", *s);
            continue;
        }

        printf("%cはその他の文字です\n", *s);
    }
}
