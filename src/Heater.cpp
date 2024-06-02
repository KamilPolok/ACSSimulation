#include "Heater.hpp"

Heater::Heater(float power)
    : nominalPower(power)
    , powerLevel(0)
{
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
