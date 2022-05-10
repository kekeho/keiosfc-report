#include <stdio.h>
#include <unistd.h>

#include "fsm-example.h"

#define MAXLEN 256

int main() {
    int state;
    char input[MAXLEN], *p;
    
    state = NODE_START;
    
    for(;;) {
        if (fsmtable[state].yes == NODE_END) {
            break;  // 終点
        }

        printf("Q: %s\n", fsmtable[state].message);
        p = fgets(input, MAXLEN-1, stdin);
        if (p != NULL) {
            if (input[0] == 'y') {
                state = fsmtable[state].yes;
            } else if (input[0] == 'n') {
                state = fsmtable[state].no;
            } else {

            }
        } else {
            break;
        }
    }

    printf("%s\n", fsmtable[state].message);
    return 0;
}