#include <errno.h>
#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char* argv[]){

	if(system(argv[1]) == -1){
		perror("system");
		return -1;
	}
	printf("El comando terminó de ejecutarse\n");
}	
