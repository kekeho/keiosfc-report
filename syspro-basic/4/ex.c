#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 256

struct kotae {
  unsigned int tsuru;
  unsigned int kame;
};


int solve(unsigned int atama, unsigned int ashi, struct kotae *p);


int main() {
    struct kotae result;
    unsigned int atama, ashi;
    char input[MAXLEN];
    char *r; int ret, solvestatus;

    printf("頭の数, 足の数: ");
    r = fgets(input, MAXLEN, stdin);
    if (r == NULL) {
        printf("ERROR: 文字列の読み取り失敗\n");
        exit(-1);
    }
    ret = sscanf(input, "%d,%d", &atama, &ashi);
    if (ret <= 0) {
        printf("ERROR: 数字を正しく入力してください\n");
        exit(-1);
    }

    solvestatus = solve(atama, ashi, &result);
    if (solvestatus < 0) {
        printf("ERROR: 入力された数字の値が不正です\n");
        exit(-1);
    }

    printf("【答え】鶴: %d羽, 亀: %d匹\n", result.tsuru, result.kame);

    return 0;
}


int solve(unsigned int atama, unsigned int ashi, struct kotae *p) {
    if (ashi % 2) {
        // 足が奇数はありえない
        return -1;
    }

    if (ashi < 2*atama) {
        // 足が頭*2より少ないことはありえない
        return -1;
    }


    p->kame = (ashi/2) - atama;
    p->tsuru = atama - p->kame;

    return 0;
}
