#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *f1(void *arg) {
    int i;
    for(i=0; i<5; i++) {
        printf("f1 out");
        usleep(1);  // このタイミングでf2が実行されて, 手前のprintfと後ろのprintfが連続して行われるという保証がない
        printf(" f1 call no. %d\n", i);
    }

    return NULL;
}


void *f2(void *arg) {
    int i;
    for (i = 0; i < 5; i++) {
        printf("f2 out");
        usleep(1);
        printf(" f2 call no. %d\n", i);
    }

    return NULL;
}


int i;
pthread_t tid[2];


int main() {
    pthread_create(&tid[0], NULL, f1, (void *)1);
    pthread_create(&tid[1], NULL, f2, (void *)1);

    for(i=0; i<2; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("all threads terminated\n");

    return 0;
}
