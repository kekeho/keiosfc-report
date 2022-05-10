#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

int main() {
    int ret, month;
    char input[MAXLINE];

    printf("何月ですか");
    fgets(input, MAXLINE, stdin);
    ret = sscanf(input, "%d", &month);
    if (ret <= 0) {
        printf("Invalid input\n");
        exit(1);
    }

    switch (month) {
        case 1:
            printf("1月は31日です\n");
            break;
        case 2:
            printf("2月は28日です\n");
            break;
        default:
            printf("%d月はわかりません\n", month);
    }

    return 0;
}