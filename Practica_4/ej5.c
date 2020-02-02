#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char* argv[]){
	int fd1, fd2;
	char buffer[256];
	if((fd = open("pipe1", O_RDONLY | O_NONBLOCK)) == -1){
		perror("open");
		return -1;
	}
	
	if((fd = open("pipe2", O_RDONLY)) == -1){
		perror("open");
		return -1;
	}
		
	if(write(fd, "hola\n", 5) == -1){
		perror("write");
		return -1;
	}
	return 1;
	
}
