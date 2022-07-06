#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    pid_t pid;

    if (argc < 2) {
        exit(1);
    }

    pid = strtol(argv[1], NULL, 10);
    if (pid > 0) {
        kill(pid, SIGTERM);
    }

    exit(0);
}

