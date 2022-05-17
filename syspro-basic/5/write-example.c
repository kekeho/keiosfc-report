#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char hello[15] = "Hello C World\n";
    write(1, hello, strlen(hello));
    exit(0);
}
