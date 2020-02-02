#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
	if (setuid(0) == -1){
		printf("setuid error: %i --> %s\n", errno, strerror(errno));
	}
	return 1;
}

