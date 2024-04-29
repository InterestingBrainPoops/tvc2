#pragma once
#include <ArduinoEigen.h>

using Eigen::Matrix;
using Eigen::Vector3f;
typedef Matrix<float, 6, 1> Vector6f;
typedef Matrix<float, 6, 6> Matrix6f;
typedef Matrix<float, 2, 6> Matrix26f;
typedef Matrix<float, 3, 3> Matrix3f;

class OrientationEstimator
{
private:
    Matrix6f F;
    Matrix26f G;
    Matrix6f P;
    Matrix6f Q;
    Matrix3f R;
    Vector6f w;
    Vector3f v;
};