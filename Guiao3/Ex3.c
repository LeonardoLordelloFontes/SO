#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	
	for (int i = 1; i < argc; i++) {
		if (fork() == 0) {
			execlp(arg[i], arg[i], NULL);
			perror(arg[i]);
			return 1;
		}
	}
	
	for (int i = 1; i < argc; i++) {
		wait(NULL);
	}
	return 0;
}
