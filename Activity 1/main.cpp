#include "mbed.h"

Serial pc(SERIAL_TX, SERIAL_RX);

InterruptIn button(USER_BUTTON);
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

Timeout button_debounce_timeout;
float debounce_time_interval = 0.3;

// Ticker interrupt is used to make the colour cycle at 1s interval
Ticker cycle_ticker;
float cycle_time_interval = 1.0;

float display_interval = 0.5;

// Set up value N; initialise user input counter
const int N = 6;
int record_led[N];
int counter = 0;

// Set up variables t's for display and record and playback
int ledsequence[3] = {1,2,3};
int t = 0;
int t_ondisplay = 0;

void onButtonStopDebouncing(void);
void onDisplayTicker(void);

void allset(void){
    led1 = true;
    led2 = true;
    led3 = true;
}

void onButtonPress(void)
{
    record_led[counter] = ledsequence[t-1];
    counter += 1;
    if (counter == N)
    {
        cycle_ticker.attach(onDisplayTicker, display_interval);
    }
    button.rise(NULL);
    button_debounce_timeout.attach(onButtonStopDebouncing, debounce_time_interval);
    if (counter < N) {
    allset();
    }
}

void onButtonStopDebouncing(void)
{
    button.rise(onButtonPress);
}

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

void onCycleTicker(void)
{
    t = (t%3)+1;
    select_led(ledsequence[t-1]);
}

void onDisplayTicker(void)
{
    select_led(record_led[t_ondisplay]);
    // t_ondisplay = (t_ondisplay%N)+1;
    t_ondisplay = (t_ondisplay+1)%N;
}

int main()
{
    allset();
    button.rise(onButtonPress);
    cycle_ticker.attach(onCycleTicker, cycle_time_interval);
    pc.printf("LED %d is ON.\r\n", t);
    // cycle_ticker.attach(onDisplayTicker, display_interval);
    while (true) {
        // pc.printf("LED %d is ON.\r\n", t);
        // wait_us(1000000);
    }
}