#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define PROCESS_NUM 3


int main() {
    pid_t pid;
    pid_t childlen[PROCESS_NUM];  // 子プロセスのプロセスIDを格納する配列
    int i, cnt;

    // forkにより子プロセスを生成
    for (i = 0; i < PROCESS_NUM; i++) {
        pid = fork();
        if (pid < 0) {
            // エラー
            fprintf(stderr, "FORK ERROR\n");
            exit(1);
        } else if (pid == 0) {
            // 子プロセス. forループを抜ける.
            break;
        } else {
            // 親プロセス. 子プロセスのpidを, childlenに格納.
            childlen[i] = pid;
        }
    }

    if (pid == 0) {
        // 子プロセス
        for (cnt = 0; cnt < 5+i; cnt++) {
            printf("Process %d(%d) [%d]\n", i+1, getpid(), cnt);
            sleep(1);
        }
        exit(0);
    } else {
        // 親プロセス. 子プロセスたちの終了を待つ.
        for (i=0; i < PROCESS_NUM; i++) {
            waitpid(childlen[i], NULL, 0);
        }
        printf("All processes terminated.\n");
    }

    exit(0);
}
