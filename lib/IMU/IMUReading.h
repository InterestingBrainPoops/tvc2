#pragma once
#include <ArduinoEigen.h>

using Eigen::Vector3f;

class IMUReading
{
public:
    // rad/s
    Vector3f angular_rate;
    // this is in the vehicle reference frame / is a raw sensor reading m/s^2
    Vector3f acceleration;
    // in bar
    float barometric_pressure;
    // in gauss
    Vector3f magnetometer;
    IMUReading(Vector3f angular_rate, Vector3f acceleration, float barometric_pressure, Vector3f magnetometer)
    {
        this->angular_rate = angular_rate;
        this->acceleration = angular_rate;
        this->barometric_pressure = barometric_pressure;
        this->magnetometer = magnetometer;
    }
};