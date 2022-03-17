#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	char buffer[64];
	int status;
	
	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();
		if (pid == 0){
			int size = snprintf(buffer, 64, "processo: %d, pai: %d\n", getpid(), getppid());
			(write(1, buffer, size) != -1) ? _exit(0) : _exit(1);
		}
		wait(&status);
		if (!WIFEXITED(status) || WEXITSTATUS(status))
			return 1;
	}
	return 0;
}
