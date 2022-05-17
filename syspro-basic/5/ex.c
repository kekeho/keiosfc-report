#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAXLEN 256


struct word {
    struct word *next;  // リスト構造
    char *data;
};



int main() {
    struct word *w, *bw = NULL, *fw = NULL;
    int fst = 1;
    char *p, *s;
    char buf[MAXLEN];

    while (1) {
        w = malloc(sizeof(struct word));  // struct wordの確保
        w->next = NULL;
        if (fst) {
            fw = w;
            fst = 0;
        }

        // 読み込み
        p = fgets(buf, MAXLEN, stdin);
        if (p == NULL) {
            break;
        }
        // 改行取り除き
        s = strchr(buf, '\n');
        if (s != NULL) {
            *s = '\0';
        }

        // 文字列の格納
        w->data = malloc(sizeof(char) * (strlen(buf)+1));
        snprintf(w->data, strlen(buf)+1, "%s", buf);

        // 前のwordと連結
        if (bw != NULL) {
            bw->next = w;
        }
        bw = w;
    }

    w = fw;
    while (1) {
        printf("%s\n", w->data);

        if (w->next == NULL) {
            break;
        }

        w = w->next;
    }
}
