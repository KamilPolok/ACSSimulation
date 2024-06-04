#include "ControllerIf.hpp"

ControllerIf::ControllerIf()
    : setpoint(0)
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
