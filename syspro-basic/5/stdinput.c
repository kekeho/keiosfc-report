#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUT 256


int main() {
    char input[MAXINPUT], ret;
    ret = fgets(input, MAXINPUT, stdin);
    
    if (ret == NULL) {
        return 0;
    }
    printf("Input is %u characters\n", strlen(input));

    return 0;
}


