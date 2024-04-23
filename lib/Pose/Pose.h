#ifndef POSE
#define POSE
#include <ArduinoEigen.h>

using Eigen::Vector3d;

// stores the pose of the rocket
class Pose
{
private:
public:
    // rotation about the x y and z axes
    Vector3d euler_angles;
    // angular velocity
    Vector3d angular_rate;
    // position in x y z
    Vector3d position;
    // velocity in x y z
    Vector3d velocity;

    Pose();
};
#endif