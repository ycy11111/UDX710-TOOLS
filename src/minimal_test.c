#include <stdio.h>
#include <unistd.h>

int main() {
    printf("HELLO_WORLD_STARTED\n");
    fflush(stdout);
    sleep(5);
    printf("HELLO_WORLD_EXITING\n");
    return 0;
}
