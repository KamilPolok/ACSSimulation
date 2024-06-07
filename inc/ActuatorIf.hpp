#pragma once

class ActuatorIf
{
public:
    ActuatorIf();
    
    virtual void setNominalControlVariableValue(float) = 0;
    virtual void setControlLevel(float);

    virtual float getControlVariableValue() const = 0;
    virtual float getControlLevel() const;
protected:
    float  nominalControlVariable;
    float  controlLevel;              // % (0-1)
};
