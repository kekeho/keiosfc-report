#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        // child
        // 1秒ずつiの値をprint.
        for (int i = 1; i <= 100; i++) {
            printf("%d\n", i);
            sleep(1);
        }
        

    } else {
        // parent
        sleep(5);
        kill(pid, SIGSTOP);  // 子プロセスを中断
        sleep(3);
        kill(pid, SIGCONT);  // 子プロセスを再開
        sleep(3);
        kill(pid, SIGTERM);  // 子プロセスを殺す
        wait(NULL);
    }
}
