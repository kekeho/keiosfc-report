#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
    int i, a[10];

    // 初期化
    for (i = 0; i < 10; i++) {
        a[i] = i;
    }

    // 表示
    for (i = 0; i < 10; i++){
        printf("a(%d) = %d\n", i, a[i]);
    }

    return 0;
}
