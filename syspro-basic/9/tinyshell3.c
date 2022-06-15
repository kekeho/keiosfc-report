#include "mysh.h"
#include "parse.c"


int main(int argc, char *argv[], char *envp[]) {
    char line[MAXCOMLEN];
    char command[MAXCOMLEN], *args[MAXARGS];
    int comlen;
    int status;
    pid_t pid, cpid;

    for(;;) {
        fprintf(stderr, "tinyshell > ");
        fgets(line, MAXCOMLEN, stdin);
        comlen = strlen(line);
        strncpy(command, line, comlen-1);
        command[comlen-1] = '\0';

        parse(command, args);

        if(strcmp(args[0], "bye") == 0) {
            fprintf(stderr, "exiting.\n");
            break;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            // child
            if (execvp(args[0], args) < 0) {
                perror("execvp");
                exit(1);
            }
        } else {
            // parent
            cpid = wait(&status);
            fprintf(stderr, "child process terminated (%d)\n", status);
        }
    }

    exit(0);
}
