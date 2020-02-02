#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

volatile int borrar = 0;

void borra(int signal){
	
	if (signal == SIGUSR1)
		borrar = 1;

}


int main(int argc, char* argv[]){	
	printf("%s\n", argv[0]);
	
	struct sigaction hand;
	
	hand.sa_handler = borra;
	
	if(sigaction(SIGALRM, &hand, NULL) == -1){
		perror("action1");
		return -1;
	}

	if(sigaction(SIGUSR1, &hand, NULL) == -1){
		perror("action2");
		return -1;
	}
	
	sigset_t sen;
	if(sigfillset(&sen) == -1){
		perror("fillset");
		return -1;
	}
	
	if(sigdelset(&sen, SIGALRM) == -1){
		perror("delset1");
		return -1;
	}

	if(sigdelset(&sen, SIGUSR1) == -1){
		perror("delset2");
		return -1;
	}
	
	alarm(atoi(argv[1]));
	
	sigsuspend(&sen);
	
	if(borrar == 0){
		if(unlink(argv[0]) == -1){
			perror("unlink");
			return -1;
		}
		printf("Archivo borrado.\n");
	}
	else
		printf("Archivo no borrado. Te has librado \n");
	return 1;
}
