/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <errno.h>

// stubbed to autoabort
void _exit(int status) {
    __asm__ volatile ("int3");
    for (;;);
};
int _close(int file) {
    (void)file;
    errno = EBADF;
    return -1;
};
// char **environ; /* pointer to array of char * strings that define the current environment variables */
int _execve(char *name, char **argv, char **env) {
    (void)name; (void)argv; (void)env;
    errno = ENOENT;
    return -1;
}

int _fork(void) {
    errno = ENOSYS;
    return -1;
}

int _fstat(int file, struct stat *st) {
    (void)file; (void)st;
    errno = EBADF;
    return -1;
}

int _getpid(void) {
    errno = ENOSYS;
    return -1;
}

int _isatty(int file) {
    if (file == 0 || file == 1 || file == 2)
        return 1;
    errno = EBADF;
    return 0;
}

int _kill(int pid, int sig) {
    (void)pid; (void)sig;
    errno = EINVAL;
    return -1;
}

int _link(char *old, char *new) {
    (void)old; (void)new;
    errno = ENOSYS;
    return -1;
}

off_t _lseek(int file, off_t ptr, int dir) {
    (void)file; (void)ptr; (void)dir;
    errno = ESPIPE;
    return (off_t)-1;
}

int _open(const char *name, int flags, ...) {
    (void)name; (void)flags;
    errno = ENOENT;
    return -1;
}

int _read(int file, char *ptr, int len) {
    (void)file; (void)ptr; (void)len;
    errno = EBADF;
    return -1;
}

caddr_t _sbrk(int incr) {
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

int _stat(const char *file, struct stat *st) {
    (void)file; (void)st;
    errno = ENOENT;
    return -1;
}

clock_t _times(struct tms *buf) {
    (void)buf;
    errno = ENOSYS;
    return (clock_t)-1;
}

int _unlink(char *name) {
    (void)name;
    errno = ENOENT;
    return -1;
}

int _wait(int *status) {
    (void)status;
    errno = ECHILD;
    return -1;
}

int _write(int file, char* ptr, int len) {
    int result;
    __asm__ volatile (
        "int $0x80"
        : "=a"(result)
        : "a"(1), "b"(file), "c"(ptr), "d"(len) 
        : "memory"
    );
    return result;
};
int _gettimeofday(struct timeval* p, void* __tz) {
    (void)p; (void)__tz;
    errno = ENOSYS;
    return -1;
}