#include "mbed.h"

// Green LED
DigitalOut led1(LED1);
// Blue LED
DigitalOut led2(LED2);
// Red LED
DigitalOut led3(LED3);


void select_led(int l)
{
        if (l==0) {
                led1 = false;
                led2 = false;
                led3 = false;
        }
        else if (l==1) {
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
        else if (l==-1) {
                led1 = true;
                led2 = true;
                led3 = true;
        }
}



int main() {
         int t=0;
         while(true) {
                select_led(t);
                wait(0.5);
                // t=(t%3)+1;
                
                // /* Seqence {0,1,2,3,-1,0...} #1
                t=(t%4)+1;
                if (t==4) t=-1;
                // */
                // /* Seqence {0,1,2,3,-1,0...} #1
                // (t+2)%5-1;
                // */
        }
}