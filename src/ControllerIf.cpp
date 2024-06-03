#include "ControllerIf.hpp"

ControllerIf::ControllerIf(Room* controlObject_, Heater* actuator_)
    : setpoint(0), controlObject(controlObject_), actuator(actuator_)
{    
}

void ControllerIf::setSetpoint(float specifiedValue)
{
    setpoint = specifiedValue;
}

void ControllerIf::setControlObject(Room* const room)
{
    controlObject = room;
}

void ControllerIf::setActuator(Heater* const heater)
{
    actuator = heater;
}
