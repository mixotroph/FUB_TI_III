#include <stdlib.h>
#include <stdio.h>

void main() {
  int *x =  malloc(1000000000000);
  if (x == NULL)
    printf("Error\n");
  else{
    printf("Erfolg\n");
    free(x);
  }
  printf("%d\n",sizeof(size_t));
}


