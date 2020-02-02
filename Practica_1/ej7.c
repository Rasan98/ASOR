#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main() {
	long aux;
	if ((aux = sysconf(_SC_ARG_MAX)) == -1){
		printf("arg error: %i --> %s\n", errno, strerror(errno));
		return -1;
	}
	printf("LongMax --> %li\n", aux);
	
	if ((aux = sysconf(_SC_CHILD_MAX)) == -1){
                printf("child error: %i --> %s\n", errno, strerror(errno));
                return -1;
        }
        printf("ChildMax --> %li\n", aux);
	
	if ((aux = sysconf(_SC_OPEN_MAX)) == -1){
                printf("open error: %i --> %s\n", errno, strerror(errno));
                return -1;
        }
        printf("OpenMax --> %li\n", aux);
	
	return 1;
}

