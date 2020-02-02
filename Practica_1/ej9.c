#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	
        printf("UID -->  %i\nEUID --> %i\n", getuid(), geteuid());
	
	return 1;
}

