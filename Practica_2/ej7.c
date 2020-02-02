#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	mode_t old = umask(757);		
	if(open(argv[1], O_CREAT|O_RDONLY, 00645) == -1){
		perror("open");
		return -1;
	}
}
