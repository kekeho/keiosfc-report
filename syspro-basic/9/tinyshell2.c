#include "mysh.h"

int main(int argc, char *argv[], char *envp[]) {
    char line[MAXCOMLEN];
    char command[MAXCOMLEN];
    int comlen;
    int status;
    pid_t pid, cpid;

    for(;;) {
        fprintf(stderr, "tinyshell> ");
        fgets(line, MAXCOMLEN, stdin);
        comlen = strlen(line);
        strncpy(command, line, comlen-1);  // 改行コード無視
        command[comlen-1] = '\0';

        if (strcmp(command, "bye") == 0) {
            // commandがbyeだったら, 終了
            fprintf(stderr, "exiting.\n");
            break;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            // child process
            if (execl(command, command, (char *)NULL) < 0) {
                perror("execl");
                exit(1);
            }
        } else {
            // parent process
            cpid = wait(&status);  // 子プロセスの終了を待つ
            fprintf(stderr, "child process terminated(%d)\n", status);
        }
    }

    exit(0);
}