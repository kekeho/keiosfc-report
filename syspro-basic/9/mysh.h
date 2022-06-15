#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXCOMLEN 1024
#define MAXARGS 1024


void parse(char *, char *[]);
