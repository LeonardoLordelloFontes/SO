#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	char buffer[64];
	int size = snprintf(buffer, 64, "processo: %d, pai: %d\n", getpid(), getppid());
	write(1, buffer, size);
	return 0;
}
