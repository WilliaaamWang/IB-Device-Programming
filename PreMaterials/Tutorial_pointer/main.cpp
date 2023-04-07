#include "mbed.h"

Serial pc(SERIAL_TX, SERIAL_RX);

float f_1(float x)
{
    // return(x-x*x);
    return x*x;
}

float first_derivative( float (*f)(float), float x)
{
    float h = 0.001;
    float dfdx;
    dfdx = ( f(x+h) - f(x-h)) / (2*h);
    return dfdx;
}

// float (*f)(float) declares the pointer that points to the function f which takes a float parameter and returns a float
// N.B. a function name is already treated by the compiler as a pointer to the function code
float second_derivative( float (*f)(float), float x)
{
    float h = 0.001;
    float d2fdx2;
    d2fdx2 = ( f(x-h) - 2 * f(x) + f(x+h) ) / (h*h);
    return d2fdx2;
}


int main() {
    pc.baud(9600);
    // float x=1.;
    float x=2.;

    pc.printf("Function Pointer test program. \r\n");

    pc.printf("Function value: f(%f)=%f \r\n", x, f_1(x));

    pc.printf("First derivative: %f \r\n", first_derivative(f_1, x));

    pc.printf("Second derivative: %f \r\n", second_derivative(f_1, x));

}