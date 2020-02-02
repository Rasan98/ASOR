#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
int main(int argc, char* argv[]){

	struct addrinfo hints;
	struct addrinfo *res, *aux;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;
	if(getaddrinfo(argv[1], NULL, &hints, &res) != 0){
		fprintf(stderr, "gai --> %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	char buf[NI_MAXHOST];
	for(aux = res; aux != NULL; aux = aux->ai_next){
	
		if(getnameinfo(aux->ai_addr, aux->ai_addrlen, buf, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) != 0){
			fprintf(stderr, "gai --> %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("%s   %i   %i\n", buf, aux->ai_family, aux->ai_socktype);
	}
	return 1;
}
