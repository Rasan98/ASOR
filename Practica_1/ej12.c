#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

int main() {
	time_t t;	
	if ((t = time(NULL)) == -1){
		printf("time error --> %i: %s", errno, strerror(errno));
		return -1;
	}
	
	printf("Time --> %i\n", t);

	return 1;
}

