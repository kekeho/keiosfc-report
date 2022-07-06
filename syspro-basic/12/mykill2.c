#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {
    pid_t pid;
    if (argc < 3) {
        exit(1);
    }

    pid = strtol(argv[2], NULL, 10);
    if (pid > 0) {
        if (strcmp("SIGSTOP", argv[1]) == 0) {
            kill(pid, SIGSTOP);
        } else if (strcmp("SIGCONT", argv[1]) == 0) {
            kill(pid, SIGCONT);
        } else if (strcmp("SIGTERM", argv[1]) == 0) {
            kill(pid, SIGTERM);
        }
    }

    exit(0);
}
