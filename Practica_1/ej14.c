#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

int main() {
	struct tm* local;	
	time_t t;
	
	if((t = time(NULL)) == -1){
		printf("time error --> %i: %s", errno, strerror(errno));
                return -1;
	}
	
	local = localtime(&t);

	printf("Year --> %d\n", 1900 + local->tm_year);

	return 1;
}

