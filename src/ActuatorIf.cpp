#include "ActuatorIf.hpp"

ActuatorIf::ActuatorIf(const std::string& controlVariableName_)
 : controlVariableName(controlVariableName_), controlLevel(0.0f)
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

const std::string& ActuatorIf::getControlVariableName() const
{
    return controlVariableName;
}
