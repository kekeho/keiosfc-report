#include "mysh.h"


void parse(char *com, char *args[]) {
    int i = 0;

    // check args
    while (*com != '\0') {

        // スペースかタブが来るまで, ポインタをインクリメントする
        while (*com == ' ' || *com == '\t') {
            *com = '\0';
            com++;
        }

        if (i >= MAXARGS-1) {
            break;
        }

        if (*com != '\0') {
            args[i] = com;
            i++;
        }

        while (*com != ' ' && *com != '\t' && *com != '\0') {
            com++;
        }
    }

    args[i] = NULL;
    return;
}
