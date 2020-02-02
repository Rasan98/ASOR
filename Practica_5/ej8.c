#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#define BUF_SIZE 500

int main(int argc, char *argv[]){
	struct addrinfo hints;
      	struct addrinfo *result, *rp;
        int sfd, s;
        struct sockaddr_storage peer_addr;
        socklen_t peer_addr_len;
        ssize_t nread;
        char buf[BUF_SIZE];

        if (argc != 3) {
            fprintf(stderr, "Usage: %s host port\n", argv[0]);
            exit(EXIT_FAILURE);
        }

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
        hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
        hints.ai_protocol = 0;          /* Any protocol */
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;

        s = getaddrinfo(argv[1], argv[2], &hints, &result);
        if (s != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            exit(EXIT_FAILURE);
        }
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
              	if (sfd == -1)
			continue;

               	if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   	break;                  /* Success */

               	close(sfd);
        }

        if (rp == NULL) {               /* No address succeeded */
        	fprintf(stderr, "Could not bind\n");
               	exit(EXIT_FAILURE);
        }

        freeaddrinfo(result);           /* No longer needed */
	
	if(listen(sfd, 5) == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}	

        for (;;) {
        	peer_addr_len = sizeof(struct sockaddr_storage);
		int clisfd;
		if((clisfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_len)) == -1){
			perror("accept");
			continue;
		}
		int pid = fork();
		if(pid == -1){
			perror("fork");
			exit(EXIT_FAILURE);
		} 
		else if(pid == 0){
	               	char host[NI_MAXHOST], service[NI_MAXSERV];
	
	               	s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
	              	
			if (s == 0)
	                	printf("PID --> %i |Connection established with %s:%s\n", getpid(), host, service);
	               	else
	                   	fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
			
			while(nread = recv(clisfd, buf, BUF_SIZE, 0)){
				printf("%s\n");
	               		if (send(clisfd, buf, nread, 0) != nread)
	                   		fprintf(stderr, "Error sending response\n");
			}
			exit(0);
		}
		else{
			close(clisfd);
		}
	}
}

