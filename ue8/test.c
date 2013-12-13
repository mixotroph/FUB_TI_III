#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

void Done(void); 
const char * const BrokenFunction(void); 

int main() 
{ 
    printf("You wrote: `%s'\n", BrokenFunction()); 
    return 0; 
} 

const char * const BrokenFunction(void) 
{ 
    char buf[128]; 
    gets(buf); 
    return strdup(buf); 
} 

void Done(void) 
{ 
    printf("Got it!\n"); 
    exit(0); 
} 
