#pragma once
#include "ControllerIf.hpp"

class PIDController : public ControllerIf
{
public:
    PIDController();
    PIDController(float, float, float);
    void control(float) override;
private:
    const float kp;     // proportional gain
    const float ki;     // intgeral gain
    const float kd;     // derrivative gain

    float errorIntegral;
    float previousError;

    float porportionalTerm(float);
    float integralTerm(float, float);
    float derrivativeTerm(float, float);
};
