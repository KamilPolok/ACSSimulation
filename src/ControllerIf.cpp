#include "ControllerIf.hpp"

ControllerIf::ControllerIf()
    : setpoint(0)
{    
}

void ControllerIf::setSetpoint(float setpoint_)
{
    setpoint = setpoint_;
}

void ControllerIf::setControlObject(ControlObjectIf* const controlObject_)
{
    controlObject = controlObject_;
}

void ControllerIf::setActuator(ActuatorIf* const actuator_)
{
    actuator = actuator_;
}
