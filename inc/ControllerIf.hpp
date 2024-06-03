#pragma once
#include "Room.hpp"
#include "Heater.hpp"

class ControllerIf
{
public:
    ControllerIf(Room* controlObject_, Heater* actuator_);
    virtual void control(float dt) = 0;
    void setSetpoint(float);
    void setControlObject(Room* const);
    void setActuator(Heater* const);
protected:
    float setpoint;
    Room* controlObject;
    Heater* actuator;
};
