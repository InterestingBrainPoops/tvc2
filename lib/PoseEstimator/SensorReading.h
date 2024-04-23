#pragma once
#include <ArduinoEigen.h>

using Eigen::Vector3d;

class SensorReading
{
public:
    Vector3d angular_rate;
    Vector3d acceleration;
    SensorReading(Vector3d angular_vel, Vector3d trans_accel)
    {
        angular_rate = angular_vel;
        acceleration = trans_accel;
    }
};