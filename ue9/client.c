/* client.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUF 1024

int main (int argc, char **argv) {
  int create_socket;
  char *buffer = malloc (BUF);
  /*
   */
  struct sockaddr_in address;
  
  int size;
  
  if ( argc < 2 ){
     printf("Usage: %s ServerAdresse\n", *argv);
     exit(EXIT_FAILURE);
  }

  /* Socket anlegen: 
   * Protokollfamilie: AF_INET => TCP/IP			
   * Socket-Typ: SOCK_STREAM für TCP
   * Protokoll: 0 (Standart) 
   */
  if ((create_socket=socket (AF_INET, SOCK_STREAM, 0)) > 0)
    printf ("Socket wurde angelegt\n");

  address.sin_family = AF_INET;     // Adressfamilie
  address.sin_port = htons (15000); // Portnummer
  
  /* konvertiert IP-Adresse der Kommandozeile (String) 
   * in nummerischen Wert*/
  inet_aton (argv[1], &address.sin_addr);

  /* Verbundungsaufbau:
   */
  if (connect ( create_socket,
                (struct sockaddr *) &address,
                sizeof (address)) == 0)
    printf ("Verbindung mit dem Server (%s) hergestellt\n",
       inet_ntoa (address.sin_addr));

  do {
      size = recv(create_socket, buffer, BUF-1, 0);
      if( size > 0)
         buffer[size] = '\0';
      printf ("Nachricht erhalten: %s\n", buffer);
      if (strcmp (buffer, "quit\n")) {
         printf ("Nachricht zum Versenden: ");
         fgets (buffer, BUF, stdin);
	 /* Nachricht versenden
	  */
         send(create_socket, buffer, strlen (buffer), 0);
       }
  } while (strcmp (buffer, "quit\n") != 0);
  
  /* Verbindung schließen */
  close (create_socket);
  return EXIT_SUCCESS;
}

