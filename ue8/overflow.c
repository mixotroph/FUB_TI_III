/* Compiliert mit gcc (Ubuntu/Linaro 4.8.1-10ubuntu9) 4.8.1*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[1];

    /* Grundaetzlich kein Zugang gestattet*/
    int access = 0;

    printf("Input: ");
    scanf("%s", &buffer);

    /* Ueberpruefung,  ob user zugangsberechtigt...*/
    if (access  != 0)
        printf("Access granted!");
    else 
        printf("Access denied");
    
    printf("\nInhalt von access: 0x%x (hex, little endian)\n",access);
    return 0;
}
