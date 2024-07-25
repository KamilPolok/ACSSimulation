#pragma once
#include <string>

class ActuatorIf
{
public:
    ActuatorIf(const std::string& controlVariableName_="Control Variable");
    
    virtual void setNominalControlVariableValue(float) = 0;
    virtual void setControlLevel(float);

    const std::string& getControlVariableName() const;
    virtual float getControlVariableValue() const = 0;
    virtual float getControlLevel() const;
protected: 
    std::string controlVariableName;
    float nominalControlVariable;
    float controlLevel;              // % (0-1)
};
