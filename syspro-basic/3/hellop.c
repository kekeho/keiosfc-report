#include <stdio.h>

int main() {
    char a[8];
    char *p;

    a[0] = 'H'; a[1] = 'E'; a[2] = 'L'; a[3] = 'L'; a[4] = 'O'; a[5] = '\n';

    // p(文字列のスタート地点)を一つづつ遅らせていく
    for (p = a; *p != '\0'; p++) {
        printf("%s\n", p);
    }

    return 0;
}
