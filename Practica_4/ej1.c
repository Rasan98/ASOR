#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char* argv[]){
	
	int fd[2];
	
	if(pipe(fd) == -1){
		perror("pipe");
		return -1;
	}
	
	int pid; 
	if((pid = fork()) == -1){
		perror("fork");
		return -1;
	}
	
	if (pid == 0){
	//hijo	
		if(close(fd[1]) == -1){
			perror("close_hijo");
			return -1;
		}
	
		if(dup2(fd[0], 0) == -1){
			perror("dup_hijo");
			return -1;
		}
		
		if(close(fd[0]) == -1){
			perror("close2_hijo");
			return -1;
		}
		
		if(execlp(argv[3], argv[3], argv[4], NULL) == -1){
			perror("exec_padre");
			return -1;
		}
	}
	else{
	//padre
		if(close(fd[0]) == -1){
			perror("close_padre");
			return -1;
		}

		if(dup2(fd[1], 1) == -1){
			perror("dup_padre");
			return -1;
		}
	
		if(close(fd[1]) == -1){
			perror("close2_padre");
			return -1;
		}

		if(execlp(argv[1], argv[1], argv[2], NULL) == -1){
			perror("exec_padre");
			return -1;
		}
	}
	
}
