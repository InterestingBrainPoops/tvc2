#pragma once
#include <ArduinoEigen.h>
#include <Pose.h>
#include <SensorReading.h>
class PoseEstimator
{
public:
    virtual void updateEstimate(SensorReading &reading);

    virtual Pose getEstimate();
};

/*
pose estimator
takes in sensor reading and then updates its pose estimate
sensor reading takes what form?
could be a generic that you input. or it could just be the assumption that since its an imu, and as such are provided with acceleration data for x y and z, and angular rate values from the gyroscope. this would have to change once we get stuff like the barometric pressure sensor and the magnetometer, but lets worry about that later
*/