#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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
    int fd;
    pid_t pids[LINHAS];
    pid_t pid;
    
    fd = open("matriz.dat", O_CREAT|O_TRUNC|O_RDWR, 0666);
    
    if (fd == -1)
    	return 1;
    
    if (write(fd, matriz, sizeof(int)*LINHAS*COLUNAS) == -1)
    	return 1;

    for (int i = 0; i < LINHAS; i++) {
    	lseek(fd, i*COLUNAS, SEEK_SET);
        if ((pid = fork()) == 0) {
            int linha[COLUNAS];
            size_t lidos = read(fd, linha, sizeof(int) * COLUNAS);
            for (int j = 0; j < COLUNAS; j++) {
                if (atoi(argv[1]) == linha[j]) {
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
		write(1, buffer, size);
    	}
    	else {
		char buffer[64];
		int size = snprintf(buffer, 64, "o número %d NÃO foi encontrado\n", atoi(argv[1]));
		write(1, buffer, size);
	}
    }
    
    return WIFEXITED(status) ? 0 : 1;
}
