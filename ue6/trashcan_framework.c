/**
 * File: trashcan.c
 * TI 2 - Betriebs- und Kommunikationssysteme
 * Freie Universitaet Berlin
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE			1024
#define PATHSIZE		256
#define TRASHFOLDER	".ti3_trash"	

char copy_buffer[BUFSIZE];

int copy(char *source, char *target)
{
  size_t bytes_read;

  /* Create new file. */
  int fd_target = open (target, O_WRONLY | O_EXCL | O_CREAT, 0700);
  if (fd_target == -1) {
    /* An error occurred. Print an error message and bail. */
    perror ("open target");
    return 1;
  }

  /* Open file to read from*/
  int fd_source = open (source,O_RDONLY);
  if (fd_source == -1) {
    /* An error occurred. Print an error message and bail. */
    perror ("open source");
    return 1;
  }

  /* Read from the file, one chunk at a time. Continue until read
   * “comes up short”, that is, reads less than we asked for. 
   * This indicates that we’ve hit the end of the file. */
  do {
    /* Read the next line’s worth of bytes. */
  
    bytes_read = read (fd_source, copy_buffer, BUFSIZE); 
    int i;
    int size = BUFSIZE;
    for (i=0; i<BUFSIZE;++i) {
      if (copy_buffer[i]== 0x00)
        size = i;
    }
    write (fd_target, copy_buffer, size);
  }
  while (bytes_read == sizeof (copy_buffer));
  close (fd_source);
  close (fd_target);
}

char parse_command(char *command)
{
	return command[1];
}


/* erzeugt einen Ordner foldername */
int setup_trashcan(char *foldername)
{
  mkdir(foldername,0700);
}

/* führt trashcan -p[ut] filename aus */
int put_file(char *foldername, char *filename)
{
  char str[100+sizeof(foldername)+sizeof(filename)]="./";
  strcat(str,foldername);
  strcat(str,"/");
  strcat(str,filename);
  copy(filename,str);
  unlink(filename);
}


/* führt trashcan -g[et] filename aus */
int get_file(char *foldername, char *filename)
{
  char str[100+sizeof(foldername)+sizeof(filename)]="./";
  strcat(str,foldername);
  strcat(str,"/");
  strcat(str,filename);
  copy(str,filename);
  remove(str);
}

/* führt trashcan -r[emove] filename aus */
int remove_file(char *foldername, char *filename)
{
  char str[100+sizeof(foldername)+sizeof(filename)]="./";
  strcat(str,foldername);
  strcat(str,"/");
  strcat(str,filename);
  remove(str);
}


int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("...not enough arguments!\n");
		return EXIT_FAILURE;
	} else {
		setup_trashcan(TRASHFOLDER);
		char command = parse_command(argv[1]);
		switch (command) {
			case 'p':
				if (argc != 3) {
					printf("...not enough arguments!\n");
					return EXIT_FAILURE;
				}
				int p_error = put_file(TRASHFOLDER, argv[2]);
				switch (p_error) {
					case -1:
						printf("...source file not found!\n");
						break;
					case -2:
						printf("...trash file was not created!\n");
						break;
					case -3:
						printf("...source file could not be removed!\n");
					default:
						break;
				}
				break;
			case 'g':
				if (argc != 3) {
					printf("...not enough arguments!\n");
					return EXIT_FAILURE;
				}
				int g_error = get_file(TRASHFOLDER, argv[2]);
				switch (g_error) {
					case -1:
						printf("...trash file not found!\n");
						break;
					case -2:
						printf("...restore file was not created!\n");
						break;
					case -3:
						printf("...trash file could not be removed!\n");
					default:
						break;
				}
				break;
			case 'r':
				if (argc != 3) {
					printf("...not enough arguments!\n");
					return EXIT_FAILURE;
				}
				int r_error = remove_file(TRASHFOLDER, argv[2]);
				if (r_error)
					printf("...trash file could not be removed!\n");
				break;
			default :
				printf("...unknown command!\n");
				return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
