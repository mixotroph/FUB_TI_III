/* compiliert mit  gcc (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3
 */

#include <stdio.h>

/* Definition von globalen Variablen.
 * Diese Variablen können überall im Programm verändert werden.
 */
int anz = 10;
int max = 0;
int array[10] = {4, 6, 2, 0, 9, 1, 5, 7, 8, 3};

/* Diese Funktion vergleicht und sortiert die beiden Feldeinträge
   "i1" und "i2" im Array "array".
 */
void exchange(int i1, int i2) {
    int tmp;
    if (array[i1] > array[i2]) {
        if (array[i1] > max)
            max = array[i1];
    } else {
        if (array[i2] > max)
            max = array[i2];
        tmp = array[i1];
        array[i1] = array[i2];
        array[i2] = tmp;
    }
}

int main()
{
    int i, j;
    for(i=0; i<anz; i++) {
        for(j=i+1; j<anz; j++)
            exchange(i, j);
    }
    printf("Die Zahlen in sortierter Reihenfolge:");
    for(i=0; i<anz; i++)
        printf(" %d", array[i]);

    printf("\nDas Maximum: %d\n", max);
    return 0;
}
