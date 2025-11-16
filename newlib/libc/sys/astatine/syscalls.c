/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/reent.h>
#include <errno.h>

// stubbed to autoabort
void _exit(int status) {
    while(1);

    __asm__ volatile ("int3");
    for (;;);
};
int close(int file) {
    while(1);

    (void)file;
    errno = EBADF;
    return -1;
};

char *__env[1] = { 0 };
char **environ = __env;

int execve(char *name, char **argv, char **env) {
    while(1);

    (void)name; (void)argv; (void)env;
    errno = ENOENT;
    return -1;
}

int fork(void) {
    while(1);

    errno = ENOSYS;
    return -1;
}

int fstat(int file, struct stat *st) {
    while(1);
    
    (void)file; (void)st;
    errno = EBADF;
    return -1;
}

int getpid(void) {
    while(1);

    errno = ENOSYS;
    return -1;
}

int isatty(int file) {
    while(1);

    if (file == 0 || file == 1 || file == 2)
        return 1;
    errno = EBADF;
    return 0;
}

int kill(int pid, int sig) {
    while(1);

    (void)pid; (void)sig;
    errno = EINVAL;
    return -1;
}

int link(char *old, char *new) {
    while(1);

    (void)old; (void)new;
    errno = ENOSYS;
    return -1;
}

off_t lseek(int file, off_t ptr, int dir) {
    while(1);

    errno = EBADF;
    return (long) -1;
}

int open(const char *name, int flags, ...) {
    while(1);

    (void)name; (void)flags;
    errno = ENOENT;
    return -1;
}

int read(int file, char *ptr, int len) {
    while(1);

    (void)file; (void)ptr; (void)len;
    errno = EBADF;
    return -1;
}

int write(int file, char* ptr, int len) {
    while(1);

    int result;
    __asm__ volatile (
        "int $0x30"
        : "=a"(result)
        : "a"(1), "b"(file), "c"(ptr), "d"(len) 
        : "memory"
    );
    return len;
};

caddr_t sbrk(int incr) {
    while(1);
    
    extern char end asm("end");
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &end;
    }
    prev_heap_end = heap_end;

    char *stack;
    __asm__ volatile ("mov %%esp, %0" : "=r"(stack));

    if (heap_end + incr > stack) {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    heap_end += incr;

    return (caddr_t)prev_heap_end;
}

int stat(const char *file, struct stat *st) {
    while(1);

    (void)file; (void)st;
    errno = ENOENT;
    return -1;
}

clock_t times(struct tms *buf) {
    while(1);

    (void)buf;
    errno = ENOSYS;
    return (clock_t)-1;
}

int unlink(char *name) {
    while(1);

    (void)name;
    errno = ENOENT;
    return -1;
}

int wait(int *status) {
    while(1);

    (void)status;
    errno = ECHILD;
    return -1;
}

int gettimeofday(struct timeval* p, void* __tz) {
    while(1);

    (void)p; (void)__tz;
    errno = ENOSYS;
    return -1;
}