#include "Heater.hpp"
#include <sstream>
#include <stdexcept>

Heater::Heater(float power)
    : powerLevel(0)
{
    setNominalPower(power);
}

void Heater::setNominalPower(float power)
{
    if (power <= 0 )
    {
        std::stringstream info;
        info << "Power has to be positive" << power;
        throw std::invalid_argument(info.str());
    }
    nominalPower = power;
}

void Heater::setPowerLevel(float level)
{
    if (level > 1)
        powerLevel = 1;
    else if (level < 0)
        powerLevel = 0;
    else
        powerLevel = level;
}

float Heater::getPowerLevel()
{
    return powerLevel;
}

float Heater::getCurrentPower()
/*Pi = P * power_level*/
{
    return nominalPower * powerLevel;
}

float Heater::getEmitedHeat(float dt)
/* q = Pi * dt*/
{
    return getCurrentPower() * dt;
}
