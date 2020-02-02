#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
	int i = 0;
	for (; i <= 255; i++){
		printf("%i --> %s\n", i, strerror(i));
	}
	return 1;
}

