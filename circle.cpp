#include <Servo.h>

#include <Wire.h>
#include <Arduino.h>
Servo thing2;
Servo thing1;

int tick = 0;
void setup(void)
{
    thing1.attach(23);
    thing2.attach(22);

    delay(100);
}

void loop()
{
    tick += 1;
    thing2.write((int)(sinf(tick / 50.0) * 33.0) + 90);
    thing1.write((int)(cos(tick / 50.0) * 33.0) + 90);

    delay(2);
}