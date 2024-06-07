#include "ActuatorIf.hpp"

ActuatorIf::ActuatorIf()
 : controlLevel(0.0f)
 {
 }

void ActuatorIf::setControlLevel(float level)
{
    if (level > 1)
        controlLevel = 1.0f;
    else if (level < 0)
        controlLevel = 0.0f;
    else
        controlLevel = level;
}

float ActuatorIf::getControlLevel() const
{
    return controlLevel;
} 