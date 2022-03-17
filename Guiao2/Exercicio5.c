#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define LINHAS 10
#define COLUNAS 1000
#define RANGE 50

int** getRandomIntMatriz(int linhas, int colunas, int range) {
    int** matriz = malloc(sizeof(int*) * linhas);
    srand(time(NULL));

    for (int i = 0; i < linhas; i++) {
        matriz[i] = malloc(sizeof(int) * colunas);
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand() % range;
        }
    }
    return matriz;
}

int main(int argc, char *argv[]) {
    int** matriz = getRandomIntMatriz(LINHAS, COLUNAS, RANGE);
    int status;
    pid_t pid;
    
    for (int i = 0; i < LINHAS; i++) {
        if ((pid = fork()) == 0) {
            for (int j = 0; j < COLUNAS; j++) {
                if (atoi(argv[1]) == matriz[i][j])
                    _exit(1);
            }
            _exit(0);
        }
    }
    
    for (int i = 0; i < LINHAS; i++) {
    	wait(&status);
    	if (WEXITSTATUS(status) || !WIFEXITED(status)) 
            break;
    }
    
    if (WIFEXITED(status)) {
    	if (WEXITSTATUS(status)) {
		char buffer[32];
		int size = snprintf(buffer, 32, "o número %d foi encontrado\n", atoi(argv[1]));
		if (write(1, buffer, size) == -1)
			return 1;
    	}
    	else {
		char buffer[64];
		int size = snprintf(buffer, 64, "o número %d NÃO foi encontrado\n", atoi(argv[1]));
		if (write(1, buffer, size) == -1)
			return 1;
	}
    }
    
    return WIFEXITED(status) ? 0 : 1;
}
