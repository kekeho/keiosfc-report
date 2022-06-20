#include <stdio.h>

void f1(int n) {
    static int sum=0;  // staticすると, スコープは関数の中だが, 2回目以降の呼び出しで初期化されないようにできたりする.
    sum = sum + n;
    printf("sum=%d\n", sum);
}


int main() {
    f1(1);
    f1(2);
    f1(4);
}
