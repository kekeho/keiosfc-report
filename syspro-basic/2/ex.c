#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

// 課題

int main(int argc, char const *argv[]) {
    int32_t a = 123;
    int64_t b = 456;
    int32_t c[10];
    char d = 'C';
    char e[10] = "INUKAWAII";
    int *p = &a;

    for (int i = 0; i < 10; i++ ){
        c[i] = i;
    }

    printf("a = %d, &a = %p, size = %ld\n", a, &a, sizeof(a));
    printf("b = %ld, &b = %p, size = %ld\n", b, &b, sizeof(b));
    printf("c[0] = %d, c = %p, size = %ld\n", c[0], c, sizeof(c));
    printf("d = %c, &d = %p, size = %ld\n", d, &d, sizeof(d));
    printf("e[] = %s, e = %p, size = %ld\n", e, e, sizeof(e));
    printf("p = %p, &p = %p, size = %ld\n", p, &p, sizeof(p));

    return 0;
}
