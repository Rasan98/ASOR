#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
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
            fprintf(stderr, "Usage: %s host port\n", argv[0]);
            exit(EXIT_FAILURE);
        }

	memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
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

           /* getaddrinfo() returns a list of address structures.
 *               Try each address until we successfully bind(2).
 *                             If socket(2) (or bind(2)) fails, we (close the socket
 *                                           and) try the next address. */
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

           /* Read datagrams and echo them back to sender */
	while ()
	for (;;) {
		fd_set sel;
		FD_ZERO(&sel);
		FD_SET(0, &sel);	
		FD_SET(sfd, &sel);	
		
		select((sfd + 1), &sel, NULL, NULL, NULL);
		if(FD_ISSET(0, &sel)){
			read(0, buf, 2);
			
			if(buf[0] == 't'){
				time_t t;
				if ((t= time(NULL)) == -1){
					perror("time");
					continue;
				}
				struct tm *loc;
				if ((loc = localtime(&t)) == NULL){
					fprintf(stderr, "localtime\n");
					continue;
				}
				char hora[40];
				int tam_h = strftime(hora, 40, "%r", loc);
				hora[tam_h++] = '\n';	
	                   	write(1, hora, tam_h);
			}
			else if(buf[0] == 'd'){
	               		time_t t;
				if ((t = time(NULL)) == -1){
					perror("time");
					continue;
				}
				struct tm *loc;
				if ((loc = localtime(&t)) == NULL){
					fprintf(stderr, "localtime\n");
					continue;
				}
				char date[40];
				int tam_date = strftime(date, 40, "%F", loc);
				date[tam_date++] = '\n';	
	                   	write(1, date, tam_date);	
			}
			else if (buf[0] == 'q'){
				printf("Saliendo\n");
				break;
			}
			else
				printf("Comando '%c' no soportado\n", buf[0]);
	
		}
		else if (FD_ISSET(sfd, &sel)){
			peer_addr_len = sizeof(struct sockaddr_storage);
			nread = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);
	            
			if (nread == -1)
	             		continue;               /* Ignore failed request */
	
	            	char host[NI_MAXHOST], service[NI_MAXSERV];
	
	            	s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
	           
			if (s == 0)
	                	printf("Received '%c' from %s:%s\n", buf[0], host, service);
	               	else
	                   	fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
			if(buf[0] == 't'){
	               		time_t t;
				if ((t= time(NULL)) == -1){
					perror("time");
					continue;
				}
				struct tm *loc;
				if ((loc = localtime(&t)) == NULL){
					fprintf(stderr, "localtime\n");
					continue;
				}
				char hora[40];
				int tam_h = strftime(hora, 40, "%r", loc);
	
				if (sendto(sfd, hora, tam_h, 0, (struct sockaddr *) &peer_addr, peer_addr_len) != tam_h)
	                   	fprintf(stderr, "Error sending response\n");
			}
			else if(buf[0] == 'd'){
	               		time_t t;
				if ((t = time(NULL)) == -1){
					perror("time");
				continue;
				}
				struct tm *loc;
				if ((loc = localtime(&t)) == NULL){
					fprintf(stderr, "localtime\n");
					continue;
				}
				char date[40];
				int tam_date = strftime(date, 40, "%F", loc);
	
				if (sendto(sfd, date, tam_date, 0, (struct sockaddr *) &peer_addr, peer_addr_len) != tam_date)
	                   	fprintf(stderr, "Error sending response\n");
			
			}
			else if (buf[0] == 'q'){
				break;
				printf("Saliendo\n");
			}
			else
				printf("Comando '%c' no soportado\n", buf[0]);
		}		
	}
	return 1;
}
