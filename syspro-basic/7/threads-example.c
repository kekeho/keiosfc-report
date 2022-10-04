/**
 * Copyright (c) 2022 Hiroki Takemura (kekeho)
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_t.h>
#include <unistd.h>


#define NUM_THREADS 3

void *do_work(void *);



int main() {
    int i;

    int pm[NUM_THREADS] = {2, 3, 4};
    pthread_t tid[NUM_THREADS];

    pthread_create(&tid[0], NULL, do_work, &pm[0]);
    pthread_create(&tid[1], NULL, do_work, &pm[1]);
    pthread_create(&tid[2], NULL, do_work, &pm[2]);

    for(i=0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("all threads terminated\n");
    
    return 0;
}


void *do_work(void *arg) {
    int j, *sleep_time;
    sleep_time = arg;

    for (j=0; j<5; j++) {
        printf("Thread %ld:%d\n", (long)pthread_self(), j);
        sleep(*sleep_time);
    }

    return 0;
}
