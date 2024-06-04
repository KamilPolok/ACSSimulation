#include "PIDController.hpp"

PIDController::PIDController()
    : kp(4.0), ki(0.02), kd(0.1), errorIntegral(0), previousError(0)
{
}

PIDController::PIDController(float kp_, float ki_, float kd_)
    : kp(kp_), ki(ki_), kd(kd_), errorIntegral(0), previousError(0)
{
}

void PIDController::control(float dt)
/* 
    Generates control value based on control values of proportional, integral and
    derrivative term:
    e(t) = r(t) - y(t); u(t) = u_p(t) + u_i(t) + u_d(t)
*/
{
    float processVariable = controlObject->getTemperature();
    float error = setpoint - processVariable;
    float controlVariable = porportionalTerm(error) + integralTerm(error, dt) + derrivativeTerm(error, dt);
    actuator->setPowerLevel(controlVariable);
}

float PIDController::porportionalTerm(float error)
/* 
    Generates control value proportional to the error:
    u_p(t) = K_p * e(t)
*/
{
    return kp * error;
}

float PIDController::integralTerm(float error, float dt)
/* 
    Generates control value  that accounts for past values of error and integrates it
    over time:
    u_i(t) = K_i * integral_of_e; integral_of_e = integral_of_e + e * dt
*/
{
    errorIntegral =+ error * dt;
    return errorIntegral * ki;
}

float PIDController::derrivativeTerm(float error, float dt)
/*
    Generatees a control value that accounts for the best estimate of the future trend
    of error, based on its current rate of change:
    u_d(t) = K_d * de; de = (e(t) - e(t_previous)) / dt
*/
{   
    float errorDifference = error - previousError;
    previousError = error;
    return kd * (errorDifference) / dt;
}
