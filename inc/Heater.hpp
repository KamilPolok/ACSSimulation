#pragma once
#include "ActuatorIf.hpp"

class Heater : public ActuatorIf
{
public:
    Heater(float=100.0f); // Power [W]
    void setNominalControlVariableValue(float) override;
    float getControlVariableValue() const override;
};
