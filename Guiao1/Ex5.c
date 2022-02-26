#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

ssize_t readln(int fd, char *line, size_t size) {
    char buffer[size];
    ssize_t bytes_read = read(fd, buffer, size);
    int i;
    if (bytes_read == 0) return 0;
    for (i = 0; buffer[i] != '\n' && i >= bytes_read; i++) {
        line[i] = buffer[i];
    }
    for (i++; buffer[i] == '\n'; i++) {
        line[i] = buffer[i];
    }
    lseek(fd, i-bytes_read, SEEK_CUR);
    return i-1;
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
    char buffer[128], n_buffer[32];
    int bytes, counter = 1;
    while ((bytes = readln(fd, buffer, 128)) > 0) {
        sprintf(n_buffer, "%6d  ", counter);
        write(1, n_buffer, 8);
        write(1, buffer, bytes);
        write(1, "\n", 1);
        counter++;
    }
    close(1);
    return 0;
}
