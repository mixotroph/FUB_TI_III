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
    write (fd_target, copy_buffer, BUFSIZE);
  }
  while (bytes_read == sizeof (copy_buffer));
  close (fd_source);
  close (fd_target);
}

int main(int argc, char *argv[])
{
  if (argc != 3){
    printf("...not enough arguments!\n");
    return EXIT_FAILURE;
  }
  char* source = argv[1];
  char* target = argv[2];
  copy(source,target);
}
