#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

	execl("/bin/ls", "ls", "-l", NULL);
	perror("ls");
	return 1;
}
