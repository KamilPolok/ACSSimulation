#pragma once
#include "ControlObjectIf.hpp"
#include "ActuatorIf.hpp"

class ControllerIf
{
public:
    ControllerIf();
    virtual void control(float dt) = 0;
    void setSetpoint(float);
    void setControlObject(ControlObjectIf* const);
    void setActuator(ActuatorIf* const);
protected:
    float setpoint;
    ControlObjectIf* controlObject;
    ActuatorIf* actuator;
};
