#pragma once
#include "IMUReading.h"
template <class T>
class IMU
{
public:
    virtual void zero(int sample_count);
    virtual IMUReading get_reading();
};

class RawIMU
{
public:
    virtual IMUReading getReading()
    {
    }
};