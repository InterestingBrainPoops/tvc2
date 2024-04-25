#pragma once
#include "PoseEstimator.h"
#include "math.h"
using Eigen::Matrix3f;
using Eigen::Vector3f;
class Integrator : public PoseEstimator
{
private:
    Pose estimate;
    float dt;

public:
    Integrator(float delta_time)
    {
        dt = delta_time;
    }
    void updateEstimate(SensorReading &reading)
    {
        estimate.heading += reading.angular_rate * dt;
        estimate.angular_rate = reading.angular_rate;
        // rotate the acceleration vector from local into global coordinates
        float ca = cosf(estimate.heading[2]);
        float sa = sinf(estimate.heading[2]);
        float cb = cosf(estimate.heading[1]);
        float sb = sinf(estimate.heading[1]);
        float cg = cosf(estimate.heading[0]);
        float sg = sinf(estimate.heading[0]);

        Matrix3f rotation{
            {{ca * cb, ca * sb * sg - sa * cg, ca * sb * cg + sa * sg},
             {sa * cb, sa * sb * sg + ca * cg, sa * sb * cg - ca * sg},
             {-sb, cb * sg, cb * cg}}};
        Vector3f global_accel = rotation * reading.acceleration;
        estimate.position += estimate.velocity * dt;
        estimate.velocity += global_accel * dt;
    }

    Pose getEstimate()
    {
        return estimate;
    }
};