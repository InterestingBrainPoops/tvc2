#include "Pose.h"

Pose::Pose()
{
    euler_angles = {0.0, 0.0, 0.0};
    angular_rate = {0.0, 0.0, 0.0};
    position = {0.0, 0.0, 0.0};
    velocity = {0.0, 0.0, 0.0};
}