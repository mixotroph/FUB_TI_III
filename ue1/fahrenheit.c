#include <stdio.h>

main() {
  float gradC, fahrenheit;
  printf("Hello, please type a temperature in Celsius (e.g. 23.0): ");
  scanf("%f", &gradC);
  fahrenheit = ((9.0/5.0)*gradC)+32; 
  printf("%f °C are  %f Fahrenheit!\n",gradC,fahrenheit);
}
