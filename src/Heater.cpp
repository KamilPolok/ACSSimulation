#include "Heater.hpp"
#include <sstream>
#include <stdexcept>

Heater::Heater(float nominalPower_)
{
    setNominalControlVariableValue(nominalPower_);
}

void Heater::setNominalControlVariableValue(float nominalPower_)
/*
    Args:
        power_: Nominal power of the heater
*/
{
    if (nominalPower_ <= 0.0f )
    {
        std::stringstream info;
        info << "Power has to be positive" << nominalPower_;
        throw std::invalid_argument(info.str());
    }
    nominalControlVariable = nominalPower_;
}

float Heater::getControlVariableValue() const
/*
    Returns:
        res: Current power = Nominal power * Power level
*/
{
    return nominalControlVariable * controlLevel;
}
