#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


#define NUM_THREADS 24
#define NUM_DATA 100000


void *do_calc(void *);
pthread_t tid[NUM_THREADS];
int param[NUM_THREADS];

double sum;
double psum[NUM_THREADS];
double data[NUM_DATA];


int main() {
    int i;
    for (i = 0; i < NUM_DATA; i++) {
        data[i] = random() / 1000000.0;
    }
    for (i = 0; i < NUM_THREADS; i++) {
        param[i] = i;
        pthread_create(&tid[i], NULL, do_calc, &param[i]);
    }
    for(i=0; i<NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    sum = 0.0;
    for(i=0; i<NUM_THREADS; i++) {
        sum += psum[i];
    }
    printf("Result(thread) = %f\n", sum);

    return 0;
}


void *do_calc(void *arg) {
    int i, j, inum, istart, iend, *id;
    double p, t;
    id = (int *)arg;
    p = 0.0;

    inum = NUM_DATA / NUM_THREADS;
    istart = *id * inum;
    iend = istart + inum;

    for(i=istart; i<iend; i++) {
        t = data[i];

        for(j=0; j<5000; j++) {
            t = j0(t);
        }
        data[i] = t;
        p += data[i];
    }

    psum[*id] = p;
    pthread_exit(NULL);
}
