// Damit die Tabelle korrekt dargestllt wird, muss 
// der Terminal eine Mindestbreite aufweisen (Vollbild)

#include <stdio.h>
#define KNRM "\x1B[0m"
#define KBLU "\x1B[34m"

main () {
  int i; float fahrenheit;
  printf("Fahrenheit |");
  for ( i=-30; i<=100; i=i+10) {
    printf("%s| %5.1f",KNRM,(float) i);
  }
  printf("\n%s° Celsius  |",KBLU);
  for ( i=-30; i<=100; i=i+10) {
    fahrenheit = (9.0/5.0*i)+32;
    printf("%s| %5.1f",KBLU,fahrenheit);
  }
  printf("\n");
}
