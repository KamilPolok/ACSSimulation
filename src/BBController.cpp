#include "BBController.hpp"

BBController::BBController(float specifiedValue)
    : ControllerIf(specifiedValue)
{  
}

float BBController::control(float processVariable, float dt)
/* control of type bang-bang (on-off) */
{
    return (processVariable < setpoint) ? 1 : 0;
}
