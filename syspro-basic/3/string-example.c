#include <stdio.h>
#include <string.h>
#include <strings.h>

#define MAXLINE 256


int main(int argc, char const *argv[]) {
    char str1[MAXLINE], str2[MAXLINE];
    char str3[MAXLINE*2];
    char *s;

    printf("1番目の文字列を入力してください\n");
    fgets(str1, MAXLINE, stdin);
    printf("2番目の文字列を入力してください\n");
    fgets(str2, MAXLINE, stdin);
    printf("str1は%sです\n", str1);
    printf("str2は%sです\n", str2);

    s = strchr(str1, '\n');  // str1の中で\nが含まれている場所を探して, その位置(ポインタ)を返す
    if (s != NULL) {
        *s = '\0';
    }

    s = strchr(str2, '\n');
    if (s != NULL) {
        *s = '\0';
    }

    strcpy(str3, str1); // strcpy(dest, from)
    printf("str3に%sがコピーされた\n", str3);
    
    strcat(str3, str2); // str3 + str2
    printf("str3にstr2をくっつけると%sになる\n", str3);

    return 0;
}
