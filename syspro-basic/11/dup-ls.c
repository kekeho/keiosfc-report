#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    int fd;
    pid_t pid;

    fd = open("output", O_WRONLY | O_CREAT, 0777);
    pid = fork();

    if (pid == 0) {
        // child
        dup2(fd, 1);  // fd(outputファイル)を複製. 番号を1にする.
        execl("/bin/ls", "ls", (char *)NULL);
    } else {
        // parent
        printf("parent's process id = %d\n", (int)getpid());
    }

    exit(0);
}
