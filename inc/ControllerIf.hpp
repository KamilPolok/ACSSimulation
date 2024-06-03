#pragma once

class ControllerIf
{
public:
    ControllerIf(float specifiedValue=0) : setpoint(specifiedValue) {}
    virtual float control(float processVariable, float dt) = 0;
    void setSetpoint(float specifiedValue) {setpoint = specifiedValue;}
protected:
    float setpoint;
};
