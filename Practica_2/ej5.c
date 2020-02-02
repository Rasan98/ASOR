#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(nt argc, char* argv[]){
		
	if(open(argv[1], O_CREAT|O_RDONLY, 00645) == -1)
		perror("open");

	perror("hola");

}
