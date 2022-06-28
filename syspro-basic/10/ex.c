#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAMELEN 10
#define NLISTLEN 4



struct name {
  char first[NAMELEN];
  char last[NAMELEN];
};


int namecmp(struct name *, struct name *);
void printnames(struct name *, size_t nsize);


int main() {
    struct name nlist[NLISTLEN] = {
        {"Taro","Keio"},
        {"Hanako", "Keio"},
        {"Yuichi", "Fukuzawa"},
        {"Eiichi", "Shibusawa"}
    };

    printf("=== ソート前 ===\n");
    printnames(nlist, NLISTLEN);
    qsort(nlist, NLISTLEN, sizeof(struct name), (void *)namecmp);
    printf("=== ソート後 ===\n");
    printnames(nlist, 4);
}


int namecmp(struct name *a, struct name *b) {
    // aの方が先→0を返す
    // bの方が先→1を返す

    // 姓で並べ替え
    for (size_t i = 0; i < NAMELEN; i++) {
        if ((unsigned char)a->last[i] < (unsigned char)b->last[i]) return 0;
        if ((unsigned char)a->last[i] > (unsigned char)b->last[i]) return 1;
    }

    // 名で並べ替え
    for (size_t i = 0; i < NAMELEN; i++) {
        if ((unsigned char)a->first[i] < (unsigned char)b->first[i]) return 0;
        if ((unsigned char)a->first[i] > (unsigned char)b->first[i]) return 1;
    }

    return 0; // 同じ文字列であれば, とりあえず0
}


void printnames(struct name *namelist, size_t nsize) {
    for (size_t i = 0; i < nsize; i++) {
        printf("%s %s\n", namelist[i].first, namelist[i].last);
    }
}
