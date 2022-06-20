#include <stdio.h>
#include <string.h>

union UnionSample {
    int nInt;
    short nShort;
    char str[10];
};


int main() {
    union UnionSample uni;
    uni.nInt = 10;
    uni.nShort = 11;
    strcpy(uni.str, "HELLO\0");

    printf("uni.nInt = %d, %p\n", uni.nInt, &uni.nInt);
    printf("uni.nShort = %d, %p\n", uni.nShort, &uni.nShort);
    printf("uni.str = %s, %p\n", uni.str, uni.str);
}
