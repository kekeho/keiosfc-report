#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>



#define OBJ_LEN 20
#define MAXLEN 8


int main(){
    int fd_shm, ret;
    const char *shm_name = "myshm";
    long shm_len = OBJ_LEN;
    long *shm_data;
    char input[MAXLEN], *s;


    // create shm obj
    fd_shm = shm_open(shm_name, O_CREAT | O_RDWR, 0600);  // get fd
    if (fd_shm == -1) {
        perror("shm_open");
        exit(1);
    }

    ret = ftruncate(fd_shm, shm_len);  // set size of shm
    if (ret < 0) {
        perror("ftruncate");
        exit(1);
    }

    // mapping shm -> shm_data
    shm_data = (long *) mmap(NULL, shm_len * sizeof(long), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (shm_data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    shm_data[0] = 10;


    for(;;) {
        s = fgets(input, MAXLEN, stdin);
        if (s == NULL) {
            break;
        }
        shm_data[1] = strtol(input, NULL, 10);
    }

    shm_unlink(shm_name);   // delete shm obj
    return 0;
}
