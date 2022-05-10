// vector

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 256


typedef struct {
    int x;
    int y;
    int z;
} vector;


void vector_add(vector *a, vector *b, vector *ret) {
    ret->x = a->x + b->x;
    ret->y = a->y + b->y;
    ret->z = a->z + b->z;
    
    return;
}

void vector_sub(vector *a, vector *b, vector *ret) {
    ret->x = a->x - b->x;
    ret->y = a->y - b->y;
    ret->z = a->z - b->z;

    return;
}


int main(int argc, char const *argv[]) {
    char input[MAXLEN];
    vector a, b, add_result, sub_result;
    int ret;

    printf("x1,y1,z1 = ");
    fgets(input, MAXLEN, stdin);
    ret = sscanf(input, "%d,%d,%d", &a.x, &a.y, &a.z);
    if (ret != 3) { exit(-1); }

    printf("x2,y2,z2 = ");
    fgets(input, MAXLEN, stdin);
    ret = sscanf(input, "%d,%d,%d", &b.x, &b.y, &b.z);
    if (ret != 3) { exit(-1); }

    // calc
    vector_add(&a, &b, &add_result);
    vector_sub(&a, &b, &sub_result);

    // print
    printf("(%d,%d,%d)+(%d,%d,%d)=(%d,%d,%d)\n", a.x, a.y, a.z, b.x, b.y, b.z, add_result.x, add_result.y, add_result.z);
    printf("(%d,%d,%d)-(%d,%d,%d)=(%d,%d,%d)\n", a.x, a.y, a.z, b.x, b.y, b.z, sub_result.x, sub_result.y, sub_result.z);

    return 0;
}
