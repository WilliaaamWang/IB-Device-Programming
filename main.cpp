#include "mbed.h"
#include "stdint.h" //This allow the use of integers of a known width
#define LM75_REG_TEMP (0x00) // Temperature Register
#define LM75_REG_CONF (0x01) // Configuration Register
#define LM75_ADDR     (0x90) // LM75 address

#define LM75_REG_TOS (0x03) // TOS Register
#define LM75_REG_THYST (0x02) // THYST Register

#define MAX_BUFFER_SIZE 60


I2C i2c(I2C_SDA, I2C_SCL);

DigitalOut myled(LED3);
DigitalOut blue(LED2);

Ticker minutetimer;
InterruptIn lm75_int(D7); // Make sure you have the OS line connected to D7

Serial pc(SERIAL_TX, SERIAL_RX);

int16_t i16; // This variable needs to be 16 bits wide for the TOS and THYST conversion to work

bool alarm;
float temp;
float temperatures[MAX_BUFFER_SIZE];


void alarm_on()
{
    alarm = true;
    // The instruction below may create problems on the latest mbed compilers.
    // Avoid using printf in interrupts anyway as it takes too long to execute.
    // pc.printf("Interrupt triggered!\r\n");
}

int i = 0;

void temprecord()
{
    if (i < 60)
    {
        temperatures[i] = temp;
        i+=1;
    }
    else if (i == 60)
    {
        for(i=0; i < 60; i++)
        {
            temperatures[i] = temperatures[i + 1];
            temperatures[59] = temp;
        }
        i = 60;
    }
}


// main() runs in its own thread in the OS
int main()
{
    bool transmitted = false;
    minutetimer.attach(temprecord, 1);

    char data_write[3];
    char data_read[3];

    data_write[0] = LM75_REG_CONF;
    data_write[1] = 0x02;
    int status = i2c.write(LM75_ADDR, data_write, 2, 0);
    if (status != 0)
    { // Error
        while (1)
        {
            myled = !myled;
            thread_sleep_for(200);
        }
    }

    float tos=28; // TOS temperature
    float thyst=26; //Thyst temperature
    
    // This section of code sets the TOS register
    data_write[0]=LM75_REG_TOS;
    i16 = (int16_t)(tos*256) & 0xFF80;
    data_write[1]=(i16 >> 8) & 0xff;
    data_write[2]=i16 & 0xff;
    i2c.write(LM75_ADDR, data_write, 3, 0);

    //This section of codes set the THYST register
    data_write[0]=LM75_REG_THYST;
    i16 = (int16_t)(thyst*256) & 0xFF80;
    data_write[1]=(i16 >> 8) & 0xff;
    data_write[2]=i16 & 0xff;
    i2c.write(LM75_ADDR, data_write, 3, 0);

    // This line attaches the interrupt.
    // The interrupt line is active low so we trigger on a falling edge
    lm75_int.fall(&alarm_on);

    while (true)
    {
        if (!alarm)
        {
            // Read temperature from sensor
            data_write[0] = LM75_REG_TEMP;
            i2c.write(LM75_ADDR, data_write, 1, 1); // no stop
            i2c.read(LM75_ADDR, data_read, 2, 0);

            // Calculate temperature value in Celcius
            int16_t i16 = (data_read[0] << 8) | data_read[1];
            // Read data as twos complement integer so sign is correct
            temp = i16 / 256.0;
        }
        else if (alarm)
        {
            myled = !myled;
            blue = !blue;
            thread_sleep_for(200);
            if (!transmitted)
            {
                pc.printf("Alarm triggered\n");
                for (int j = 0; j < 60; j++)
                {
                    // Display result
                    pc.printf("Temperature = %.3f\r\n",temperatures[j]);
                }
                transmitted = true;
            }
        } 
    }
}