#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


#define NAMELEN 10


struct name {
  char first[NAMELEN];
  char last[NAMELEN];
};


int main() {
    pid_t pid;
    int fd[2], dsize, cstatus;
    struct name buf;

    struct name nlist[4] = {
        {"Taro","Keio"},
        {"Hanako", "Keio"},
        {"Yuichi", "Fukuzawa"},
        {"Eiichi", "Shibusawa"}
    };


    // pipeを作成. fd[0]: read, fd[1]: write
    if (pipe(fd) != 0) {
        perror("pipe");
        exit(1);
    }


    // fork
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    }

    if (pid == 0) {
        // child process
        close(fd[1]);  // 書き込み用は閉じる
        while (1) {
            dsize = read(fd[0], &buf, sizeof(struct name));  // pipeから読み込み
            if (dsize <= 0) break;
            printf("%s %s\n", buf.first, buf.last);
        }
        close(fd[0]);
    } else {
        // parent process
        close(fd[0]);  // 読み込み用は閉じる

        // nlistの中身を, pipe経由で子プロセスに送信
        for (int i = 0; i < 4; i++) {
            write(fd[1], &nlist[i], sizeof(struct name));
        }
        close(fd[1]);
        wait(&cstatus); // 子プロセスの終了待ち
    }
    exit(0);
}
