ssize_t readln(int fd, char *line, size_t size) {
    char c;
    ssize_t bytes_read = 0;
    while (bytes_read < size && read(fd, &c, 1) > 0 && c != '\n') {
        line[bytes_read] = c;
        bytes_read++;
    }
    return bytes_read;
}
