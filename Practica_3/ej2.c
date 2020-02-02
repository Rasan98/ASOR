#include <errno.h>
#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	int sched;

	if((sched = sched_getscheduler(getpid())) == -1){
		perror("getscheduler");
		return -1;
	}

	switch(sched){
	case SCHED_OTHER:
		printf("Policy --> other\n");
		break;
	case SCHED_FIFO:
		printf("Policy --> fifo\n");
		break;
	case SCHED_RR:
		printf("Policy --> rr\n");
		break;
	default:
		printf("Bad policy\n");
	}

	struct sched_param b;
	if(sched_getparam(getpid(), &b) == -1){
		perror("getparam");
		return -1;
	}
	
	printf("Priority --> %d\n", b.sched_priority);
	
	int prio;
	if((prio = sched_get_priority_min(sched)) == -1){
		perror("getminprio");
		return -1;
	}
	printf("Min prio --> %i\n", prio);

	if((prio = sched_get_priority_max(sched)) == -1){
		perror("getmaxprio");
		return -1;
	}
	printf("Max prio --> %i\n", prio);
	return 1;
}	
