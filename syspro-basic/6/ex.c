// n円の支払いをするとき, 何通りの効果を用いた支払い方法があるかを求める


#include <stdio.h>
#include <string.h>



int coins[6] = {100, 50, 10, 5, 1};



int change(int n, int k) {
    // 1円玉で支払う方法は一通り
    if (k == 1) {
        return 1;
    }

    // 再起の末尾
    if (n <= 0) {
        return 1;
    }

    // coins配列におけるkのインデックス
    int kidx = 0;
    for (int i = 0; i < 6; i++) {
        if (coins[i] == k) {
            kidx = i;
        }
    }

    // nがkより小さかったら, 一つ小さいコインで試す
    if (n < k) {
        return change(n, coins[kidx+1]);
    }

    return change(n, coins[kidx+1]) + change(n-k, k);
}


int main(int argc, char const *argv[]) {
    int result;

    // 1円から200円まで試す
    for (int i = 1; i <= 200; i++) {
        result = change(i, 100);
        printf("%d円 = %d通り\n", i, result);
    }
}
