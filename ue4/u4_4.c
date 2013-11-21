/* Erfolgreich compiliert mit:
 * gcc (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
   /* der Typ FILE wird in stdio.h definiert
    * Er enthaelt die noetigen Informationen, um Ein- und
    * Ausgabeoperationen durchzufuehren.
    */
    FILE    *f1;                  
    FILE    *f2;                  
    char    buf[100];             
    int     i;                    

    /* Wenn die Anzahl der Argumente nicht genau drei ist,
     * gib eine Fehlermeldung aus.
     */
    if(argc != 3)
    {
        printf("usage: u1_4a <inputfiles> <outputfile>!\n");
        exit(-1);
    }

    /* Oeffne die erste Textdatei (als erstes Argument uebergeben),
     * um aus ihr zu Lesen (modus rt)
     */
    f1 = fopen(argv[1], "rt");

    /* Falls das nicht geklappt hat, gib eine Fehlermeldung aus.
     */
    if(f1 == NULL)
    {
        printf("Error: Can't open '%s' for read!\n", argv[1]);
        exit(-1);
    }
    
    /* Oeffne die zweite Textdatei (als zweites Argument uebergeben),
     * um in ihr zu schreiben.
     */
    f2 = fopen(argv[2], "at");

    /* Falls das nicht geklappt hat, gib eine Fehlermeldung aus.
     */
    if(f2 == NULL)
    {
        printf("Error: can't open '%s' for write!\n", argv[2]);
        exit(-1);
    }
    
    /* Solange nicht das Ende der Datei erreicht wurde...
     */
    while(!feof(f1))
    {
      /* ...lese ein Zeile von byte/char_t aus dem filestream
       * in den Puffer, aber hoechstens 99 Zeichen. 
       */  
        fgets(buf, 100, f1);

        /* Fuer jedes Zeichen im Puffer...
         */
        for(i=0; i<strlen(buf); i++)
        {
          /* ...pruefe, ob es ein kleiner Buchstabe ist.
           */
            if(islower(buf[i]))
            {
              /* falls ja, wandle ihn in einen Grossbuchstben um.
               */
                buf[i] += 'A'-'a';
            }
         }
        /* Puffer in Ausgabedatei schreiben...
         */
        fputs(buf, f2); 
    }

    /* ... und beide Dateien schliessen.
     */
    fclose(f1);
    fclose(f2);
    printf("Programm Ende!\n");

    return 0;
}
