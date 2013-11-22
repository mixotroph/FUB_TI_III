/* getchar example : typewriter */ 

#include <stdio.h> 
#include <math.h>
#include <stdlib.h>

// Vereinbarung von Variablen eines anonymen Struktur-Datentyps
struct {
  int len ;
  char *str;
} *p,*p1; 

int main() {
  int n;
  p = malloc(sizeof(int)+sizeof(char*));
  p1 = malloc(sizeof(int)+sizeof(char*));
  (*p).len = 0;
  (*p1).len = 5;

  char *test = malloc(sizeof(char));
  char *test1 = malloc(sizeof(char));
  *test = 'a';
  *test1 = 'z';
  (*p).str = test;
  (*p1).str = test1;
  ++p->len;   //-> bindet stärker (2) als ++ (3)
  (*p -> str)++;
  //*p++ -> str;
  //++p->len;
  printf("Ausgabe: %d, %s\n", p->len, p->str);
  printf("Ausgabe: %d, %s\n",*(p1), *(p+3));
  free(p);
  return 0;
}
