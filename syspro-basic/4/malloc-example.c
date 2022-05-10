// malloc example

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#define MAXLINE 16

int main() {
    int len;
    char input[MAXLINE];
    char *s, *p, *q, *ret;

    ret = fgets(input, MAXLINE, stdin);
    if (ret == NULL) {
        exit(0);
    }

    s = strchr(input, '\n');
    if (s != NULL) {
        *s = '\0';
    }

    len = strlen(input);
    p = malloc(sizeof(char)*len+1);  // 確保
    strcpy(p, input);


    q = malloc(sizeof(char)*len+4);
    strcpy(q, p);
    strcat(q, "END");

    printf("*p=%s\n", p);
    printf("*q=%s\n", q);
    printf("input=%p, &len=%p\n", input, &len);
    printf("p=%p,q=%p\n",p,q);
    printf("&p=%p,&q=%p,&s=%p\n",&p,&q,&s);
    exit(0);
}


