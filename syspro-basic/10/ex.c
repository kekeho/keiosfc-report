#include <stdio.h>
#include <stdlib.h>


#define NAMELEN 10

struct name {
  char first[NAMELEN];
  char last[NAMELEN];
};


int namecmp(struct name *, struct name *);
void printnames(struct name *, int nsize);


int main() {
    struct name nlist[4] = {
        {"Taro","Keio"},
        {"Hanako", "Keio"},
        {"Yuichi", "Fukuzawa"},
        {"Eiichi", "Shibusawa"}
    };

    printf("=== ソート前 ===\n");
    printnames(nlist, 4);
    qsort(nlist, 4, sizeof(struct name), (void *)namecmp);
    printf("=== ソート後 ===\n");
    printnames(nlist, 4);
}


int namecmp(struct name *a, struct name *b) {
    // aの方が先→0を返す
    // bの方が先→1を返す

    // 姓で並べ替え
    for (size_t i = 0; i < NAMELEN; i++) {
        if (a->last[i] < b->last[i]) return 0;
        if (a->last[i] > b->last[i]) return 1;
    }

    // 名で並べ替え
    for (size_t i = 0; i < NAMELEN; i++) {
        if (a->first[i] < b->first[i]) return 0;
        if (a->first[i] > b->first[i]) return 1;
    }

    return 0; // 同じ文字列であれば, とりあえず0
}


void printnames(struct name *namelist, int nsize) {
    for (size_t i = 0; i < nsize; i++) {
        printf("%s %s\n", namelist[i].first, namelist[i].last);
    }
}
