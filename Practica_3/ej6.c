#include <errno.h>
#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int imprimir(void){

	printf("PID --> %i\n", getpid());
	printf("PPID --> %i\n", getppid());
	
	int pgid;
	if((pgid = getpgid(getpid())) == -1){
		perror("getpgid");
		return -1;
	}	
	printf("PGID --> %i\n", pgid);

	int sid;
	if((sid = getsid(getpid())) == -1){
		perror("getsid");
		return -1;
	}	
	printf("SID --> %i\n", sid);

	struct rlimit fil;
	if(getrlimit(RLIMIT_NOFILE, &fil) == -1){
		perror("getrlimit");
		return -1;
	}	
	printf("File limit --> %i\n", fil.rlim_max);

	char buf[100];
	if(getcwd(buf, 100) == NULL){
		perror("getcwd");
		return -1;
	}	
	printf("Working directory --> %s\n", buf);

	return 1;
}	

int main(int argc, char* argv[]){

	int pid = fork();
	if(pid == -1){
		perror("fork");
		return -1;
	}
	else if(pid == 0){
	//hijo		
		if(chdir("/tmp") == -1){
			perror("chdir");
			return -1;
		}
		
		int sid;
		if((sid = setsid()) == -1){
			perror("getsid");
			return -1;
		}
		if(imprimir() == -1){
			return -1;
		}
	}
	else{
	//padre
		printf("Padre PID --> %i\n", getpid());
		sleep(30);	
		return 1;
	}
}	
