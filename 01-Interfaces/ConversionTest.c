#include <assert.h>
#include <math.h>
#include "Conversion.c"
#include <stdio.h>

unsigned AreEqual(double a, double b) {
    const double epsilon = 0.001;
    if(fabs(a - b) <= epsilon) return 1;
    else return 0;
}

int main(void) {
    assert(AreEqual(Celsius(84.2), 29) == 1);
    assert(AreEqual(Celsius(77.0), 25.0) == 1);
    assert(AreEqual(Farenheit(26.0), 78.8) == 1);
    assert(AreEqual(Farenheit(10.0), 50.0) == 1);

    printf("Los tests corrieron correctamente.\n");

    return 0;
}