#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Pessoa {
	int idade;
	char nome[256];
};

int main(int argc, char* argv[]) {
	if (argc > 4) {
		fprintf(stderr, "usage: %s FLAG name age", argv[0]);
		return 1;
	}
	
	int fd = open("pessoas.dat", O_CREAT|O_RDWR, 0666);
	if (fd == -1) {
		perror(argv[0]);
		return 1;
	}
	
	struct Pessoa p;
	
	if (strcmp(argv[1], "-i") == 0) {
		int n, counter = 0;
		while ((n = read(fd, &p, sizeof(p))) == sizeof(p)) {
			if (strcmp(argv[2], p.nome) == 0) {
				fprintf(stderr, "%s already exists", argv[2]);
				close(fd);
				return 1;
			}
			counter++;
		}
		if (n == -1) {
			fprintf(stderr, "something went wrong while reading the file");
			close(fd);
			return 1;
		}
		else {
			char buffer[64];
			int size = snprintf(buffer, 64, "registo %d\n", counter);
			write(1, buffer, size);
			strcpy(p.nome, argv[2]);
			p.idade = atoi(argv[3]);
			write(fd, &p, sizeof(p));
			close(fd);
			return 0;
		}
	}
	
	if (strcmp(argv[1], "-u") == 0) {
		int found = 0, n;
		while ((n = read(fd, &p, sizeof(p)) == sizeof(p))) {
			if (strcmp(argv[2], p.nome) == 0) {
				found = 1;
				p.idade = atoi(argv[3]);
				lseek(fd, -sizeof(p), SEEK_CUR);
				write(fd, &p, sizeof(p));
				close(fd);
				return 0;
			}
		}
		if (n == -1) 
			fprintf(stderr, "something went wrong while reading the file");
		
		
		if (!found) 
			fprintf(stderr, "name not found in the file");
		
		close(fd);
		return 1;
	}
	
	if (strcmp(argv[1], "-o") == 0) {
		int n, counter = 0;
		while ((n = read(fd, &p, sizeof(p))) == sizeof(p)) {
			
			if (atoi(argv[2]) == counter) {
				p.idade = atoi(argv[3]);
				lseek(fd, -sizeof(p), SEEK_CUR);
				write(fd, &p, sizeof(p));
				close(fd);
				return 0;
			}
			counter++;
		}
		if (n == -1)
			fprintf(stderr, "something went wrong while reading the file");
		if (counter >= atoi(argv[2]))
			fprintf(stderr, "register doesn't exist\n");
		
		close(fd);
		return 1;
	}
	
	// APENAS PARA TESTES, MOSTRA O CONTEÚDO DOS REGISTOS
	
	if (strcmp(argv[1], "-s") == 0) {
		int n;
		char buffer[512];
		while ((n = read(fd, &p, sizeof(p)) == sizeof(p))) {
			int x = snprintf(buffer, 512, "name: %s; age: %d\n", p.nome, p.idade);
			write(1, buffer, x);
		}
		if (n == -1) 
			fprintf(stderr, "something went wrong while reading the file");
			
		close(fd);
		return 0;
	}
	
	// Como eu coloquei os return 0 dentro dos if's, se chegar aqui é erro
	
	fprintf(stderr, "usage: %s FLAG name age", argv[0]);
	close(fd);
	return 1;
}
