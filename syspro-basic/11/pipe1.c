#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    int fd[2], i, n;
    char buf[BUFSIZ];
    pid_t pid;


    // pipeを作成
    if (pipe(fd) != 0) {  // fd[0]: read用, fd[1]: write用
        perror("pipe");
        exit(1);
    }
    printf("Pipe input fd=%d, output fd=%d\n", fd[0], fd[1]);

    // fork
    printf("Now create new process\n");
    pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    }

    if (pid == 0) {
        // child process
        close(fd[1]);  // write用を閉じる
        printf("child's process id = %d\n", (int)getpid());
        for(;;) {
            n = read(fd[0], buf, BUFSIZ);
            if (n <= 0) {
                printf("child terminating\n");
                exit(0);
            } else {
                printf("child got data %d bytes.\n", n);
                write(1, buf, n);
            }
        }
    } else {
        // parent process
        close(fd[0]);  // read用を閉じる
        printf("parent's prpcess id = %d\n", (int)getpid());

        for(i=0; i<5; i++) {
            printf("Write Pipe No.%d\n", i);
            write(fd[1], "MESSAGE\n", 8);
            sleep(4);
        }
        close(fd[1]);
        printf("parent terminating\n");
        exit(0);
    }
    exit(0);
}
