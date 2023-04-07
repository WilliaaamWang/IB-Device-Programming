#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

const int N = 6;
int led_cycle[N]={3,2,3,1,2,1};

void select_led(int l)
{
    if (l==1) {
            led1 = true;
            led2 = false;
            led3 = false;
    }
    else if (l==2) {
            led1 = false;
            led2 = true;
            led3 = false;
    }
    else if (l==3) {
            led1 = false;
            led2 = false;
            led3 = true;
    }
}

int main() {
    int t=0;
    while(true) {
        select_led(led_cycle[t]);
        wait(0.5);
        t=(t+1)%N;
}
}