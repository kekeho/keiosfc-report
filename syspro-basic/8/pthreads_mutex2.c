#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int i;
pthread_mutex_t mutex;
pthread_t tid[2];



void *f1(void *arg) {
    int i;
    for(i=0; i<5; i++) {
        pthread_mutex_lock(&mutex);
        printf("f1 out");
        usleep(1);
        printf(" f1 call no. %d\n", i);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}


void *f2(void *arg) {
    int i;
    for (i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        printf("f2 out");
        usleep(1);
        printf(" f2 call no. %d\n", i);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}


int main() {
    pthread_create(&tid[0], NULL, f1, (void *)1);
    pthread_create(&tid[1], NULL, f2, (void *)1);

    for(i=0; i<2; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("all threads terminated\n");

    return 0;
}
