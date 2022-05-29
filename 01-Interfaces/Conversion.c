#include "Conversion.h"

double Celsius(double gradosFarenheit) {
    return (5.0/9.0)*(gradosFarenheit-32);
}

double Farenheit(double gradosCelsius) {
    return (gradosCelsius*(9.0/5.0) + 32);
}