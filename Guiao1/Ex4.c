#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

ssize_t readln(int fd, char *line, size_t size) {
    char c;
    ssize_t bytes_read = 0;
    while (read(fd, &c, 1) > 0 && c != '\n' && bytes_read < size) {
        line[bytes_read] = c;
        bytes_read++;
    }
    return bytes_read;
}

int main (int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "usage: %s [FILE]\n", argv[0]);
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
    char buffer[1024], n_buffer[32];
    int bytes, counter = 1;
    while ((bytes = readln(fd, buffer, 1024)) > 0) {
        sprintf(n_buffer, "%6d  ", counter);
        write(1, n_buffer, 8);
        write(1, buffer, bytes);
        write(1, "\n", 1);
        counter++;
    }
    return 0;
}
