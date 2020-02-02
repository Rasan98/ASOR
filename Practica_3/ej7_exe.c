#include <errno.h>
#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
int main(int argc, char* argv[]){
//	char* newargv[argc];
//	char* newenv[] = {NULL};
	
//	int i = 1;
//	for(;i < argc; i++)
//		newargv[i - 1] = argv[i];
//	argv[argc - 1] = NULL;
//
 	char aux[50];

	sprintf(aux, "/bin/%s", argv[1]);
	printf("%s\n", aux);
	argv[1] = aux;
	if(execv(argv[1], argv + 1) == -1){
		perror("exec");
		return -1;
	}
	printf("El comando terminó de ejecutarse");
}	
