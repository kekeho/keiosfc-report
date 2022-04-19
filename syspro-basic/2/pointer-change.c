#include <stdio.h>

int main(int argc, char const *argv[]){
    int x;
    int *p; // int型のポインタ変数. 「記憶場所を記憶する」.

    x = 7;
    p = &x;

    printf("&x = %p\n", &x);
    printf("p = %p, *p=%d\n", p, *p);  // *ポインタ変数 で実体にアクセス
    printf("&p = %p\n", &p);



    return 0;
}
