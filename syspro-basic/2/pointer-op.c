#include <stdio.h>


int main(int argc, char const *argv[]) {
    int a[10]; int *p;
    int i;
    for (i = 0; i < 10; i++) {
        a[i] = i;
    }
    printf("&a[0] = %p, &i=%p, &p=%p\n", &a[0], &i, &p);
    
    p = a; // ポインタをaのアドレスに
    printf("p=%p, *p=%d\n", p, *p);  // aの0番地
    p++; // ポインタをインクリメント. 型の大きさ1つぶんだけシフト(int *pなら, 4増える)
    printf("p=%p, *p=%d\n", p, *p); // aの1番地
    
    return 0;
}
