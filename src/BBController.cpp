#include "BBController.hpp"

void BBController::control(float dt)
/* control of type bang-bang (on-off) */
{
    float processVariable = controlObject->getProcessVariable();
    actuator->setControlLevel((processVariable < setpoint) ? 1.0f : 0.0f);
}
