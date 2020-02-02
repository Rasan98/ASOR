#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

volatile int sigint = 0;

volatile int sigtstp = 0;

void cuenta(int signal){

	if(signal == SIGINT)
		sigint++;
	else if (signal = SIGTSTP)
		sigtstp++;

}


int main(int argc, char* argv[]){	
	printf("%s\n", argv[0]);
	
	struct sigaction hand;
	
	hand.sa_handler = cuenta;
	
	if(sigaction(SIGINT, &hand, NULL) == -1){
		perror("action");
		return -1;
	}

	if(sigaction(SIGTSTP, &hand, NULL) == -1){
		perror("action");
		return -1;
	}
	
	sigset_t sen;
	if(sigfillset(&sen) == -1){
		perror("fillset");
		return -1;
	}
	
	if(sigdelset(&sen, SIGINT) == -1){
		perror("delset1");
		return -1;
	}

	if(sigdelset(&sen, SIGTSTP) == -1){
		perror("delset2");
		return -1;
	}
	

	int i = 0;
	for(; i < 10; i++){
		sigsuspend(&sen);
	}

	printf("SIGINT --> %i\nSIGTSTP --> %i\n", sigint, sigtstp);
	return 1;
}
