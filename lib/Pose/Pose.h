#ifndef POSE
#define POSE
#include <ArduinoEigen.h>

using Eigen::Quaternionf;
using Eigen::Vector3f;

// stores the pose of the rocket
class Pose
{
private:
public:
    // rotation about the x y and z axes (roll, pitch, yaw)
    Vector3f heading;
    // angular velocity in the vehicle reference frame
    Vector3f angular_rate;
    // position in x y z in the earths reference frame
    Vector3f position;
    // velocity in x y z in the earths reference frame
    Vector3f velocity;

    Pose();
};
#endif