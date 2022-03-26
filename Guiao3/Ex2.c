#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	int status;
	if (fork() == 0) {
		execlp("ls", "ls", "-l", NULL);
		perror("ls");
		_exit(1);
	}
	wait(&status);
	return WIFEXITED(status) ? WEXITSTATUS(status) : 127;
}
