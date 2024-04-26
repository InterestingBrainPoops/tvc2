#pragma once
class Controller
{
private:
    float integral;
    float old_reading;
    float current_reading;
    float kp, ki, kd, dt;

public:
    Controller() {}
    Controller(float p_gain, float i_gain, float d_gain, float delta_time)
    {
        kp = p_gain;
        ki = i_gain;
        kd = d_gain;
        dt = delta_time;
    }

    void update(float reading)
    {
        old_reading = current_reading;
        current_reading = reading;
    }

    float get(float setpoint)
    {
        float error = (setpoint - current_reading);

        integral += dt * error;

        return kp * error - ki * integral;
    }
};