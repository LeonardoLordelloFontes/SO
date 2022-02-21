ssize_t readln(int fd, char *line, size_t size) {
    char c;
    ssize_t bytes_read = 0;
    while (read(fd, &c, 1) > 0 && c != '\n') {
        if (bytes_read >= size) {
            fprintf(stderr, "buffer size is not enough to store the line\n");
            return -1;
        }
        line[bytes_read] = c;
        bytes_read++;
    }
    return bytes_read;
}
