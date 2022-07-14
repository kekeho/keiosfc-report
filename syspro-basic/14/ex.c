#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



int main(void) {
    char *line; line = NULL;
    __ssize_t ret;
    size_t bsize = 0;

    ret = getline(&line, &bsize, stdin);
    if (ret == -1) {  // エラー処理
        fprintf(stderr, "getline error\n");
    }

    // 10文字ずつ表示
    for (size_t i = 0; i < ret; i+=10) {
        for (size_t j = 0; j < 10; j++){
            if (*(line+i+j) == '\0') {  // 終端文字が来たらプログラムを終了
                return 0;
            }
            printf("%c", *(line+i+j));
        }
        printf("\n");
    }
}
