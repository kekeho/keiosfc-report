#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]){
    unsigned int i, j;
    i = 10; j = 15;
    printf("i=%d, &i=%p\n", i, &i);
    printf("j=%d, &j=%p\n", j, &j);
    return 0;
}
