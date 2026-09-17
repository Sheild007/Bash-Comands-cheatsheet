#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void do_heavy_work() {
    // A pointless busy loop designed to consume CPU cycles
    // This will clearly show up when we use 'perf' or generate a Flame Graph
    volatile long sum = 0;
    for (long i = 0; i < 500000000; i++) {
        sum += i;
    }
}

void leak_memory() {
    // Allocate memory but NEVER free it. 
    // Valgrind's memcheck will catch this!
    int *leaked_array = malloc(100 * sizeof(int));
    leaked_array[0] = 42; // Prevent optimization
}

void lots_of_syscalls() {
    // Open, write, and close a file repeatedly.
    // 'strace' will show thousands of openat/write/close calls here.
    for (int i = 0; i < 1000; i++) {
        int fd = open("/dev/null", O_WRONLY);
        if (fd != -1) {
            write(fd, "test\n", 5);
            close(fd);
        }
    }
}

int main() {
    printf("Starting Profiling and Debugging Target...\n");
    
    printf("1. Doing heavy CPU work...\n");
    do_heavy_work();
    
    printf("2. Leaking some memory...\n");
    leak_memory();
    
    printf("3. Spamming system calls...\n");
    lots_of_syscalls();
    
    printf("Finished!\n");
    return 0;
}
