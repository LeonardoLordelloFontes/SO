#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s source destination\n", argv[0]);
        return 1;
    }
    int sfd = open(argv[1], O_RDONLY);
    if (sfd == -1) {
        perror(argv[1]);
        return 1;
    }
    int dfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if (dfd == -1) {
        perror(argv[2]);
        return 1;
    }
    char c;
    int n;
    while((n = read(sfd, &c, 1) > 0)) {
        write(dfd, &c, 1);    
    }
    close(sfd);
    close(dfd);
    return 0;
}
