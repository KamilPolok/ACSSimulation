#pragma once
#include "ControllerIf.hpp"

class PIDController : public ControllerIf
{
public:
    PIDController(float=0);
    float control(float, float) override;
private:
    static constexpr float kp = 4.0;    // proportional gain
    static constexpr float ki = 0.02;   // intgeral gain
    static constexpr float kd = 0.1;    // derrivative gain

    float errorIntegral;
    float previousError;

    float porportionalTerm(float);
    float integralTerm(float, float);
    float derrivativeTerm(float, float);
};
