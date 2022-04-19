#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
    char a[8] = "HELLO";

    printf("&a = %p\n", &a);
    printf("a[2] = %d, &a[2] = %p\n", a[2], &a[2]);
    printf("a[]=%s\n", a);
}
