#pragma once

class Heater
{
public:
    Heater(float=100.0);

    void setNominalPower(float);
    virtual void setPowerLevel(float);

    float getPowerLevel();
    float getCurrentPower();
    float getEmitedHeat(float);
private:
    float  nominalPower;    // W
    float  powerLevel;      // % (0-1)
};
