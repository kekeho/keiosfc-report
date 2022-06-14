#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define NUM_THREADS 3

// do_workは, void型関数のポインタ
void *do_work(void *);


int main() {
    int i;
    // threadに渡す引数の定義
    int pm[NUM_THREADS] = {2, 3, 5};
    // スレッドIDを保持する配列
    pthread_t tid[NUM_THREADS];

    // pthread_create(tid格納先, attributes, void型関数のポインタ, 引数);
    pthread_create(&tid[0], NULL, do_work, &pm[0]);
    pthread_create(&tid[1], NULL, do_work, &pm[1]);
    pthread_create(&tid[2], NULL, do_work, &pm[2]);

    for (int i = 0; i < NUM_THREADS; i++) {
        // 停止を待つ
        // pthread_join(thread id, スレッドの中でpthread_exitを呼び出したときに渡した戻り値を入れるポインタ)
        pthread_join(tid[i], NULL);
    }
    printf("all threads terminated\n");
    return(0);
}


void *do_work(void *arg /*  void *は汎用ポインタ */) {
    int j, *sleep_time;
    sleep_time = (int *)arg;
    for (j = 0; j < 5; j++) {
        printf("Thread %ld: %d\n", (long)pthread_self(), j);
        sleep(*sleep_time);
    }

    return 0;
}
