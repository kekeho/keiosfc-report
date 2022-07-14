#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>



#define OBJ_LEN 10


int main() {
    int fd_shm;
    const char *shm_name = "myshm";
    long shm_len = OBJ_LEN;
    long *shm_data;

     // create shm obj
    fd_shm = shm_open(shm_name, O_CREAT | O_RDWR, 0600);  // get fd
    if (fd_shm == -1) {
        perror("shm_open");
        exit(1);
    }

    // mapping shm -> shm_data
    shm_data = (long *) mmap(NULL, shm_len * sizeof(long), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (shm_data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("shm_data[0] = %ld\n", shm_data[0]);
    printf("shm_data[1] = %ld\n", shm_data[1]);


    return 0;
}
