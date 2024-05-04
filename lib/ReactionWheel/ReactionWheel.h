#pragma once
#include <Arduino.h>
#include <Filter.h>
volatile float t0;
volatile float t1;
void light_on()
{

    t0 = t1;

    t1 = millis();
}
template <unsigned int N>
class OpticalEncoder
{
private:
    Filter<N> rpm_filter;

public:
    OpticalEncoder() {}

    OpticalEncoder<N>(int pin)
    {
        this->rpm_filter = Filter<N>();

        t0 = 0.0;
        t1 = 0.0;
        pinMode(pin, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(pin), light_on, RISING);
    }

    float get_rpm()
    {

        float current_rpm = 60000.0 / (float)((t1 - t0));
        return this->rpm_filter.update(current_rpm);
    }
};
class Motor
{
private:
    int min;
    int max;
    int current_pwm;
    int pin;

public:
    Motor() {}
    Motor(int pin, int min, int max)
    {
        this->min = min;
        this->max = max;
        this->current_pwm = min;
        this->pin = pin;
        pinMode(pin, OUTPUT);
        analogWrite(pin, 0);
        delay(500);
        analogWrite(pin, min);
    }

    void set_speed(float speed)
    {
        if (speed < 0.0)
        {
            speed = 0.0;
        }
        else if (speed > 1.0)
        {
            speed = 1.0;
        }
        this->current_pwm = (int)((float)(max - min) * speed + (float)min);
        analogWrite(this->pin, this->current_pwm);
    }

    int get_pwm()
    {
        return current_pwm;
    }

    float get_speed()
    {
        return (float)(current_pwm - min) / (float)(max - min);
    }
};
template <unsigned int N>
class ReactionWheel
{
private:
    OpticalEncoder<N> encoder;
    Motor motor;

public:
    ReactionWheel() {}
    ReactionWheel(int encoder_pin, int motor_pin, int min_pwm, int max_pwm)
    {
        motor = Motor(motor_pin, min_pwm, max_pwm);
        encoder = OpticalEncoder<N>(encoder_pin);
    }
    float get_rpm()
    {
        return this->encoder.get_rpm();
    }
    float get_speed()
    {
        return this->motor.get_speed();
    }

    void set_speed(float speed)
    {
        this->motor.set_speed(speed);
    }
};