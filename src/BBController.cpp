#include "BBController.hpp"

void BBController::control(float dt)
/* control of type bang-bang (on-off) */
{
    float processVariable = controlObject->getTemperature();
    actuator->setPowerLevel((processVariable < setpoint) ? 1 : 0);
}
