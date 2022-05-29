#include "Conversion.c"
#include <stdio.h>

int main(void){
    const int lowerFarenheit = 0;
    const int upperFarenheit = 300; 
    const int stepFarenheit = 20; 
    const int lowerCelsius = -17; 
    const int upperCelsius= 160; 
    const int stepCelsius = 10;

    printf("Tabla conversion fahrenheit a celsius:\n");
    for(int fahr = lowerFarenheit; fahr <= upperFarenheit; fahr = fahr + stepFarenheit) 
        printf("%3d %6.1f\n", fahr, Celsius(fahr));

    printf("\n");

    printf("Tabla conversion celsius a fahrenheit:\n");
    for(int celsius = lowerCelsius; celsius <= upperCelsius; celsius = celsius + stepCelsius)
        printf("%3d %6.0f\n", celsius, Farenheit(celsius));

    return 0;
}