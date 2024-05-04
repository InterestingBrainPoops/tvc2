#pragma once
#include "Arduino.h"
#include "Wire.h"
#include "Servo.h"

float clamp(int value, int middle, int range)
{
    if (value <= middle - range)
    {
        return middle - range;
    }
    else if (value >= middle + range)
    {
        return middle + range;
    }
    else
    {
        return value;
    }
}

class Gimbal
{
private:
    Servo yaw_servo;
    Servo pitch_servo;
    int yaw_angle;
    int pitch_angle;
    int yaw_z_offset;
    int pitch_z_offset;
    int clamp_range;

public:
    Gimbal() {}
    Gimbal(int yaw_pin, int pitch_pin, int yaw_zero_offset, int pitch_zero_offset, int safety_range)
    {
        yaw_servo.attach(yaw_pin);
        pitch_servo.attach(pitch_pin);
        yaw_angle = yaw_zero_offset;
        pitch_angle = pitch_zero_offset;
        pitch_z_offset = pitch_zero_offset;
        yaw_z_offset = yaw_zero_offset;
        clamp_range = safety_range;

        pitch_servo.write(pitch_zero_offset + 90);
        yaw_servo.write(pitch_zero_offset + 90);
    }
    void zero()
    {
        pitch_servo.write(90);
        yaw_servo.write(90);
    }
    void set_pitch(int angle)
    {
        pitch_angle = clamp(90 + pitch_z_offset + angle, 90 + pitch_z_offset, clamp_range);
        pitch_servo.write(pitch_angle);
    }
    void set_yaw(int angle)
    {
        yaw_angle = clamp(90 + yaw_z_offset + angle, 90 + yaw_z_offset, clamp_range);
        yaw_servo.write(yaw_angle);
    }

    int get_pitch()
    {
        return pitch_angle - 90 - pitch_z_offset;
    }
    int get_yaw()
    {
        return yaw_angle - 90 - yaw_z_offset;
    }
};