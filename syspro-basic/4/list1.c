#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct list {
    struct list *next;  // 構造体の自己参照
    char *name;
};


int main() {
    struct list *p, *q;

    p = malloc(sizeof(struct list));
    p->name = malloc(sizeof(char) * 6);
    strcpy(p->name, "START");

    q = malloc(sizeof(struct list));
    p->next = q;
    q->next = NULL;
    q->name = malloc(sizeof(char)*4);
    strcpy(q->name, "END");    

    return 0;
}