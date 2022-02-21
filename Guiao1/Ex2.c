#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "usage: %s [optional: FILE]", argv[0]);
        return 1;
    }
    int fd = 0;
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
    }
    if (fd == -1) {
        perror(argv[1]);
        return 1;
    }
    ssize_t bytes_read;
    char buffer[1024];
    while((bytes_read = read(fd, buffer, 1024)) > 0) {
        write(1, buffer, bytes_read);
    }
    close(0);
    close(1);
    return 0;
}
