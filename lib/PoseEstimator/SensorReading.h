#pragma once
#include <ArduinoEigen.h>

using Eigen::Vector3f;

class SensorReading
{
public:
    Vector3f angular_rate;
    // this is in the vehicle reference frame / is a raw sensor reading
    Vector3f acceleration;
    SensorReading(Vector3f angular_vel, Vector3f trans_accel)
    {
        angular_rate = angular_vel;
        acceleration = trans_accel;
    }
};