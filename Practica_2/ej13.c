#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int fd;	

	if((fd = open(argv[1], O_RDWR)) == -1){
		perror("Open");
		return -1;
	}

	if(dup2(fd, 1) == -1){
		perror("Dup2, 1");
		return -1;
	}

	if(dup2(fd, 2) == -1){
		perror("Dup2, 2");
		return -1;
	}

	printf("Hola holita vecinillo\n");
	fprintf(stderr, "Estupido Flanders\n");
	return 1;
}
