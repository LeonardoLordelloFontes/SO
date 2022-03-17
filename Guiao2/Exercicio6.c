#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define LINHAS 10
#define COLUNAS 1000
#define RANGE 5000

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
    int encontrado = 0;
    int naLinha[LINHAS] = {0};
    pid_t pids[LINHAS];
    pid_t pid;
    
    for (int i = 0; i < LINHAS; i++) {
        if ((pid = fork()) == 0) {
            for (int j = 0; j < COLUNAS; j++) {
                if (atoi(argv[1]) == matriz[i][j]) {
                	_exit(1);
                }
            }
            _exit(0);
        }
        else {
        	pids[i] = pid;
        }
    }
    
    for (int i = 0; i < LINHAS; i++) {
    	waitpid(pids[i], &status, 0);
    	if (!WIFEXITED(status)) 
            break;
        if (WEXITSTATUS(status)) {
        	naLinha[i] = 1;
        	encontrado = 1;
        }
    }
    
    if (WIFEXITED(status)) {
    	if (encontrado) {
		char buffer[LINHAS * 10 + 64];
		int size = snprintf(buffer, 64, "o número %d foi encontrado nas linhas: ", atoi(argv[1]));
		for (int i = 0; i < LINHAS; i++) {
			if (naLinha[i])
				size += snprintf(buffer + size, sizeof(buffer) - size, "%d ", i); 
		}
		size += snprintf(buffer + size, sizeof(buffer) - size, "\n");
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
