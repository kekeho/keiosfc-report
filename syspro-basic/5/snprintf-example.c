#include <stdio.h>
#include <stdlib.h>


int main() {
    FILE *fp;
    char name[100];

    int i;
    for(i=1; i<=5; i++) {
        snprintf(name, 100, "file%d", i);
        printf("Creating %s\n", name);
        fp = fopen(name, "w");
        fprintf(fp, "%d\n", i);
        fclose(fp);
    }

    exit(0);

}