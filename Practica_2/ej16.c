#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	int fd;	

	if((fd = open(argv[1], O_RDWR)) == -1){
		perror("Open");
		return -1;
	}

	struct flock b;
	
	if(fcntl(fd, F_GETLK, &b) == -1){
		perror("Fcntl, 1");
		return -1;
	}

	if(b.l_type == F_UNLCK)
		printf("Cerrojo desbloqueado\n");
	else{
		printf("Cerrojo bloqueado\n");
		return 1;
	}	
	
	b.l_type = F_WRLCK;	

	if(fcntl(fd, F_SETLK, &b) == -1){
		perror("Fcntl, 2");
		return -1;
	}
	
	if(dup2(fd, 1) == -1){
                perror("Dup2, 2");
                return -1;
        }

	char * buf = malloc(20*sizeof(char));
	time_t t = time(NULL);
	struct tm* hora = localtime(&t); 
	printf("%i:%i:%i", hora->tm_hour, hora->tm_min, hora->tm_sec);
	sleep(30);
	
	b.l_type = F_UNLCK;

	if(fcntl(fd, F_SETLK, &b) == -1){
                perror("Fcntl, 3");
                return -1;
        }
	
	return 1;
}
