#pragma once
#include "ArduinoEigen.h"
using Eigen::Matrix;
class Simulation
{
private:
    Matrix<float, 4, 4> A;
    Matrix<float, 2, 4> K;
    Matrix<float, 4, 2> B;

    float dt = 0.010;

public:
    Matrix<float, 4, 1> ideal_state;
    Matrix<float, 4, 1> real_state;
    Simulation(Matrix<float, 4, 1> initial_condition, Matrix<float, 4, 4> state_transition, Matrix<float, 2, 4> gains, Matrix<float, 4, 2> control_input)
    {
        A = state_transition;
        B = control_input;
        K = gains;
        this->ideal_state = initial_condition;
        this->real_state = initial_condition;
    }

    Matrix<float, 2, 1> get_control_inputs(Matrix<float, 4, 1> setpoint)
    {
        return K * (setpoint - ideal_state);
    }

    void update_ideal_state(Matrix<float, 2, 1> ideal_torques)
    {
        ideal_state = A * ideal_state * dt + B * ideal_torques * dt;
    }

    void update_real_state(Matrix<float, 2, 1> real_torques)
    {
        real_state = A * real_state * dt + B * real_torques * dt;
    }
};