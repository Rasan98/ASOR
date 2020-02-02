#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	struct stat buf;		
	if(stat(argv[1], &buf) == -1){
		perror("stat");
		return -1;
	}
	
	if((buf.st_mode & S_IFMT) != S_IFREG){
		printf("File is not a regular file\n");
		return -1;
	}
	
	int i = 0, last = 0;

	for(;i < strlen(argv[1]); i++){
		if(argv[1][i] == '/')
			last = i + 1;
	}
	
	char * sym = malloc(4*sizeof(char) + strlen(argv[1]) - last + 1);
	char * hard = malloc(5*sizeof(char) + strlen(argv[1]) - last + 1);

	strcpy(sym, &argv[1][last]);
	strcat(sym, ".sym");

	strcpy(hard, &argv[1][last]);
	strcat(hard, ".hard");

	if(link(argv[1], hard) == -1){
		perror("link");
		return -1;
	}
	
	
	if(symlink(argv[1], sym) == -1){
		perror("symlink");
		return -1;
	}

	return 1;
}
