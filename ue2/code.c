#include <stdio.h>

char test[6] = "Hallo";

void convert(char s[100]) {
}

void encode(char s[100]) {
}

void decode(char s[100]) {
}

main () {
  char wahl; 
  printf("Möchten Sie einen Text (v)erschlüsseln, oder (e)ntschlüsseln? (b zum Beenden): \n");
  scanf("%s", &wahl);
  printf("%d",(int) &wahl);
//  printf("%s Welt\n",test);
} 
