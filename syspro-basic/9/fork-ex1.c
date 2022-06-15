#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    pid_t pid;
    printf("now create new process\n");
    
    pid = fork(); // ここから分岐.
    // この時点で, 子はpid == 0, 親はpid == 子プロセスのpid となる.


    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    }

    if (pid == 0) {
        printf("child's process id =%d\n", (int)getpid());
        sleep(3);
    } else {
        printf("parent's process id = %d / %d\n", (int)getpid(), (int)pid);
        sleep(3);
    }

    return 0;
}
