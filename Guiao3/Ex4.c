#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mySystem(char * executable) {
	char *delimits = " ";
	int argc = 0;
	int size = 8;
	int status;
	char **argv = malloc(sizeof(char*) * size);
	char *token = strtok(executable, delimits);
	
	while (token != NULL) {
		argv[argc] = token;
		argc++;
		if (argc == size - 2) {
			size *= 2;
			argv = realloc(argv, sizeof(char*) * size);
		}
		token = strtok(NULL, delimits);
	}
	
	argv[argc] = NULL;
	
	if (fork() == 0) {
		execvp(argv[0], argv);
		perror(argv[0]);
		_exit(1);
	}
	wait(&status);
	
	return WIFEXITED(status) ? WEXITSTATUS(status) : 127;
}

int main(int argc, char *argv[]) {
	char buffer[32] = "ls -l";
	return mySystem(buffer);
}
