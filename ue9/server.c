/* server.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define BUF 1024

int main(int argc, char **argv) {

  if ( argc < 2 ){
     printf("Usage: %s  <port > < logpath >\n", *argv);
     exit(EXIT_FAILURE);
  }

  //int path = (int) argv[1];  
  uint16_t port = atoi( argv[1]);
  printf("Port: %d ",port);
  /*Socket-Deskriptor*/
  int create_socket, new_socket;
  socklen_t addrlen;
  time_t t;
  char *buffer = malloc (BUF);
  ssize_t size;
  struct sockaddr_in address;
  const int y = 1;

  /* File-Deskriptor*/
  FILE *log; 

  /* Socket anlegen: 
   * Protokollfamilie: AF_INET => TCP/IP			
   * Socket-Typ: SOCK_STREAM für TCP
   * Protokoll: 0 (Standart) 
   */
  if ((create_socket = socket (AF_INET, SOCK_STREAM, 0)) > 0)
    printf ("Socket wurde angelegt\n");

  setsockopt( create_socket, SOL_SOCKET,
              SO_REUSEADDR, &y, sizeof(int));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons (15000);
  
  if (bind ( create_socket,
             (struct sockaddr *) &address,
             sizeof (address)) != 0) {
    printf( "Der Port ist nicht frei – belegt!\n");
  }

  /* listen(): warten auf Verbindung
   * max. 5 Prozesse
   */
  listen (create_socket, 5);
  addrlen = sizeof (struct sockaddr_in);
  while (1) {
     /* Verbindungsaufbauwunsch
      * führt auf Gegenseite zu erfolgreichen Aufruf von connect()
      */
     new_socket = accept ( create_socket,
                           (struct sockaddr *) &address,
                           &addrlen );
     if (new_socket > 0)
      printf ("Ein Client (%s) ist verbunden ...\n",
         inet_ntoa (address.sin_addr));
     
 	log = fopen(argv[2], "at");
	/* Falls das nicht geklappt hat, gib eine Fehlermeldung aus.
     */
    if(log == NULL)
    {
        printf("Error: Can't open '%s' for read!\n", argv[2]);
        exit(-1);
    }
	 do {
        printf ("Nachricht zum Versenden: ");
        fgets (buffer, BUF, stdin);
	/* Nachricht versenden
	 */        
	send (new_socket, buffer, strlen (buffer), 0);
    time(&t);
	fputs(ctime(&t),log);
	fputs(buffer, log);
        size = recv (new_socket, buffer, BUF-1, 0);
        if( size > 0)
           buffer[size] = '\0';
        printf ("Nachricht empfangen: %s\n", buffer);
     } while (strcmp (buffer, "quit\n") != 0);
     close (new_socket);
	 fclose(log);
  }
 
  /* Verbindung schließen */
  close (create_socket);
  return EXIT_SUCCESS;
}
