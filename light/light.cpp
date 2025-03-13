#include <stdio.h>
#include <wiringPi.h>
int main()
{
    wiringPiSetup();
    pinMode(4,OUTPUT);
    while(1)
    {
        digitalWrite(4,LOW);
        delay(1000);
        digitalWrite(4,HIGH);
        delay(1000);
    }
    return 0;
}


