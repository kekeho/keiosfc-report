#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


#define NUM_DATA 100000

double data[NUM_DATA];

int main() {
    int i, j;
    double s, t;
    s = 0.0;

    for(i=0; i<NUM_DATA; i++) {
        data[i] = random() / 1000000.0;
        t = data[i];

        for(j=0; j<5000; j++) {
            t = j0(t);
        }

        data[i] = t;
        s += data[i];
    }

    printf("Result(single) = %f\n", s);
    return 0;
}
