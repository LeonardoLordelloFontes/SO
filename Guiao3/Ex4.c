#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char * delimits = " \t";
	char * copia = strcpy(copia, argv[1]);
	int len = 0;
	int status;
	for (char *token = strtok(copia, delimits); token != NULL; token = strtok(copia, delimits)) {
		len++;
	}
	
	char *string[len];
	
	for (int i = 0; i < len; i++) {
		char *token = strtok(argv[1], delimits);
		string[i] = strcpy(string[i], token);
		wait(&status);	
	}
	
	for (int i = 1; i < len; i++) {
		if (fork() == 0) {
			execvp(string[0], string);
			perror(string[0]);
			_exit(1);
		}
		wait(&status);
	}
	
	return WIFEXITED(status) ? WEXITSTATUS(status) : 127;
}
