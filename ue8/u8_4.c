#include <stdio.h>

#define square(x) x*x
#define PRINT_INTEGER(i) printf("%d ",i);
#define max(a,b) (a>b) ? a : b 
#define VERBOSE
#define isdigit(c) (c>='0' && c<='9') ? 1 :0

void main() {
    int a,b,c;

    #ifdef VERBOSE
    printf("Makrotest\n");
    #endif

    PRINT_INTEGER(square(2));
    PRINT_INTEGER(square(1+1));

    a=1;
    b=5;
    /* b gleichzeitig um 1 erhöhen */   
    printf("\nMaximum von a und b: %d\n",max(a,b++)); 
    printf("Wert von b: %d\n",b);
    printf("isdigit: %d\n",isdigit('7'));

    #ifdef VERBOSE
    printf("Test zu Ende!\n");
    #else
    printf("VERBOSE nicht definiert\n");
    #endif 
}
