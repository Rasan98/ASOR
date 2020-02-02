#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]){	
	sigset_t sen;
	if(sigemptyset(&sen) == -1){
		perror("emptyset");
		return -1;
	}
	
	if(sigaddset(&sen, SIGINT) == -1){
		perror("addset1");
		return -1;
	}

	if(sigaddset(&sen, SIGTSTP) == -1){
		perror("addset2");
		return -1;
	}
	
	if(sigprocmask(SIG_SETMASK, &sen, NULL) == -1){
		perror("procmask");
		return -1;
	}
	
	setenv("SLEEP_SECS", "15", 1);
	int secs = atoi(getenv("SLEEP_SECS"));
	
	sleep(secs);

	sigset_t pending;

	if(sigpending(&pending) == -1){
		perror("procmask");
		return -1;
	}

	int member = sigismember(&pending, SIGINT);

	if(member == -1){
		perror("ismember1");
		return -1;
	}
	else if(member)
		printf("SIGINT received\n");

	member = sigismember(&pending, SIGTSTP);

	if(member == -1){
		perror("ismember2");
		return -1;
	}
	else if(member){
		printf("SIGTSTP received\n");
		if(sigdelset(&sen, SIGINT) == -1){
			perror("delset");
			return -1;
		}
		
		if(sigprocmask(SIG_UNBLOCK, &sen, NULL) == -1){
			perror("procmask2");
			return -1;
		}
	}
	
	printf("THE END\n");
	return 1;
}
