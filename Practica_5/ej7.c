#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#define BUF_SIZE 500

int main(int argc, char *argv[])
{
        struct addrinfo hints;
        struct addrinfo *result, *rp;
        int sfd, s;
        struct sockaddr_storage peer_addr;
        socklen_t peer_addr_len;
        ssize_t nread;
        char buf[BUF_SIZE];

        if (argc != 3) {
            fprintf(stderr, "Usage: %s host port command\n", argv[0]);
            exit(EXIT_FAILURE);
        }

	memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
        hints.ai_flags = 0;    /* For wildcard IP address */
        hints.ai_protocol = 0;          /* Any protocol */
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;

        s = getaddrinfo(argv[1], argv[2], &hints, &result);
        if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            	exit(EXIT_FAILURE);
        }

           /* getaddrinfo() returns a list of address structures.
 *  *               Try each address until we successfully bind(2).
 *   *                             If socket(2) (or bind(2)) fails, we (close the socket
 *    *                                           and) try the next address. */
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            	if (sfd == -1)
                	continue;

            	if (connect(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                	break;                  /* Success */

            	close(sfd);
        }

        if (rp == NULL) {               /* No address succeeded */
            	fprintf(stderr, "Could not connect\n");
            	exit(EXIT_FAILURE);
        }

        freeaddrinfo(result);           /* No longer needed */

        while(1){
		if((nread = read(0, buf, BUF_SIZE)) == -1){
			printf("Error in shell input");
			continue;
		}
		buf[nread] = '\0';
		if(nread == 2 && buf[0] == 'Q')
			exit(0);
 
		if ((nread = send(sfd, buf, nread, 0)) != nread){
	                        perror("Error sending");
				continue;
		}
		
		if((nread = recv(sfd, buf, BUF_SIZE, 0)) == -1){
			perror("Error receiving");
			continue;
		}
	        
	        printf("%s\n", buf);
	}
	return 1;
}
