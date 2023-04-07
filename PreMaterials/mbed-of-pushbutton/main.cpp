#include "mbed.h"

DigitalIn button(USER_BUTTON);
DigitalOut led3(LED3);
DigitalOut led2(LED2);



int main()
{
    led3=0;
    led2=0;
    while (true)
    {
        if (button == 1)
        {
            led3 = false; // Red LED OFF
            led2 = true; // Blue LED ON
        }
        else
        {
            led3 = true; // Red LED ON
            led2 = false; // Blue LED OFF
        }
        wait(0.02);
    }
}

