/*
 * client-beej.c 
 * A simple client beej-style 
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <errno.h>
 #include <netdb.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>

 #define PORT "3490" // the port the client will connecting to
 #define MAXDATASIZE 100 // max number of bytes we can get at once

 /* get sockaddr, IPv4 or IPv6 
  * struct sockaddr is part of struct addrinfo and holds socket address information 
  */
 void *get_in_addr(struct sockaddr *sa) {
 	if (sa->sa_family == AF_INET) {
 		return &(((struct sockaddr_in*)sa)->sin_addr);
 	}
 	return &(((struct sockaddr_in6*)sa)->sin6_addr);
 }

 int main(int argc, char *argv[]) {
 	int sockfd, numbytes; // socked (file)descriptor
 	char buff[MAXDATASIZE];
 	struct addrinfo hints, *serverinfo, *p;
 	int rv;
 	char s[INET6_ADDRSTRLEN];

 	if (argc != 2) {
 		fprintf(stderr, "ussage: client hostname\n");
 		exit(1);
 	}

 	memset(&hints, 0, sizeof hints); // make sure the struct is empty
 	hints.ai_family = AF_UNSPEC; // IP version-agnostic
 	hints.ai_socktype = SOCK_STREAM; // lets use a two-way connected communication stream

 	/* getaddrinfo helps to set up the structs we need later.
	 * If everything works properly, servinfo will point to a linked list of struct addrinfo, 
	 * each of which contains a struct sockaddr of some kind that we can use later!
 	 */
 	if ((rv=getaddrinfo(argv[1], PORT, &hints, &serverinfo)) != 0) {
 		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
 		return 1;
 	}

 	// loop through all the results and connectto the first we can
 	for (p = serverinfo; p != NULL; p = p->ai_next) {
 		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
 			perror("client: socket");
 			continue;
 		}
 		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
 			close(sockfd);
 			perror("client: connect");
 			continue;
 		}

 		break;
 	}

 	if (p == NULL) {
 		fprintf(stderr, "client: failed to connect\n");
 		return 2;
 	}

 	/*ntop -> "network to presentation"
 	 * converts an IP in numbers-and-dots notation
 	 */
 	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), s, sizeof s);
 	printf("client: connecting to %s\n", s);

 	freeaddrinfo(serverinfo); // all done with this structure

 	if ((numbytes = recv(sockfd, buff, MAXDATASIZE-1, 0)) == -1) {
 		perror("recv");
 		exit (1);
 	}

 	buff[numbytes] ='\0';
 	printf("client: recived '%s' (%d Bytes)\n", buff, numbytes);
 	close(sockfd);
 	return 0;
 }

