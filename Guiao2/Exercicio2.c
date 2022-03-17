#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	char buffer[64];
	pid_t pid;
	int status;
	if ((pid = fork()) == 0) {
		int size = snprintf(buffer, 64, "processo: %d, pai: %d\n", getpid(), getppid());
		write(1, buffer, size);
		_exit(0);
	}
	wait(&status);
	int size = snprintf(buffer, 64, "processo: %d, pai: %d, filho: %d\n", getpid(), getppid(), pid);
	return (WIFEXITED(status) && write(1, buffer, size) != -1) ? 0 : 1;
}
