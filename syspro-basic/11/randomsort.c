#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main() {
    int fd[2], i;
    char buf[BUFSIZ];
    pid_t pid;

    if (pipe(fd) != 0) {
        perror("pipe");
        exit(1);
    }

    // pipe fd
    printf("Pipe input fd=%d, output fd=%d\n", fd[0], fd[1]);
    
    printf("Now, create new process\n");
    pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    }

    if (pid == 0) {
        // child process
        close(fd[1]);
        if(fd[0] != STDIN_FILENO) {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {  // stdinにfd[0]を付け替える
                perror("dup2");
                exit(1);
            }
            close(fd[0]);
        }
        printf("child's process id = %d\n", (int)getpid());

        if (execl("/usr/bin/sort", "sort", (char *)NULL) < 0) {
            perror("execl");
            exit(1);
        }
    } else {
        // parent process
        int status;
        pid_t cpid;  // child pid
        close(fd[0]);

        printf("parent's process id = %d\n", (int)getpid());

        for(i=0; i<10; i++) {
            snprintf(buf, BUFSIZ, "%ld\n", random());
            write(fd[1], buf, strlen(buf));
        }
        close(fd[1]);
        cpid = wait(&status);
        fprintf(stderr, "child process terminated(%d)\n", status);
        printf("parent terminating\n");
        exit(0);
    }

    exit(0);
}
