#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char* argv[]){
	int fd;
	if((fd = open("pipe", O_WRONLY)) == -1){
		perror("open");
		return -1;
	}
		
	if(write(fd, "hola\n", 5) == -1){
		perror("write");
		return -1;
	}
	return 1;
}
