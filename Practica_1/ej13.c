#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
	struct timeval start, stop;	
	
	if (gettimeofday(&start, NULL) == -1){
		printf("time start error --> %i: %s", errno, strerror(errno));
		return -1;
	}

	int i;
	for(i = 0; i < 1000000; i++);
	
	if (gettimeofday(&stop, NULL) == -1){
		printf("time stop error --> %i: %s", errno, strerror(errno));
		return -1;
	}

	printf("Time --> %i\n", stop.tv_usec - start.tv_usec);

	return 1;
}

