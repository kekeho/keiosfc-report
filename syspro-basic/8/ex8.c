#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


#define NUM_THREADS 24
#define NUM_MAX 1000


void *do_calc(void *);

pthread_t tid[NUM_THREADS];


struct param {
    int sum;
    pthread_mutex_t mutex;
};



int main() {
    int i;
    struct param p;
    p.sum = 0;

    for(i=0; i<NUM_THREADS; i++) {
        pthread_create(&tid[i], NULL, do_calc, &p);
    }

    for(i=0; i<NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("SUM: %d\n", p.sum);
    return 0;
}


void *do_calc(void *arg) {
    struct param *p = (struct param *)arg;

    int i;
    int tmp;
    for (i=0; i<NUM_MAX; i++) {
        pthread_mutex_lock(&(p->mutex));
        tmp = p->sum;
        usleep(random() % 100);
        p->sum = tmp+1;
        pthread_mutex_unlock(&(p->mutex));
    }

    pthread_exit(NULL);
}
